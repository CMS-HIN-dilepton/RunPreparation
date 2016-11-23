#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <utility>
#include <algorithm>
#include "TFile.h"
#include "TString.h"
#include "TRegexp.h"
#include "TClass.h"
#include "TKey.h"
#include "TH1.h"
#include "TProfile.h"
#include "TROOT.h"

using namespace std;
using boost::property_tree::ptree;

const double lumilength = 23.31;

// default directory for DQM files. You can find these files in https://cmsweb.cern.ch/dqm/online/data/browse/Original/00026xxxx/0002630xx/ and similar URLs.
TString basedir = "/afs/cern.ch/user/e/echapon/workspace/public/RunPrep2016/HLT_runbyrun/DQMfiles";

// default JSON file
// TString jsonfile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/HI/DCSOnly/json_DCSONLY.txt";
TString jsonfile_5tev = "/afs/cern.ch/user/e/echapon/workspace/public/RunPrep2016/HLT_runbyrun/DQMfiles/json_5tev.txt";
TString jsonfile_8tev = "/afs/cern.ch/user/e/echapon/workspace/public/RunPrep2016/HLT_runbyrun/DQMfiles/json_8tev.txt";
TString jsonfile = jsonfile_5tev;

// some global variables to store the executable parameters, as requested by the user
string theType    = "HLT";
string theHlttype = "accept";
bool   dorate     = false;
bool   dotime     = false;
string outputfile = "NONE";
double lumifactor = -1.;
TString pattern   = ".*";
vector<TRegexp> patterns;
const double magicfactor_5tev = 4.17e-7;
const double magicfactor_8tev = 5.35e-7;
double magicfactor=magicfactor_5tev;
bool   nooutput   = true;
int    rebin      = 1;
bool   extrapol   = false;

// this structure is intended to contain a pair<run number, <lumi section start, lumi section stop>>
typedef vector<pair<int,pair<int,int> > > lumirange;

// this class is intended to contain a tripletI of integers, e.g. run number, lumi section, count
// typedef tuple<int,int,int> tripletI;
template <typename T> class triplet {
   public:
      int i0;
      int i1;
      T   i2;

      triplet(int a0, int a1, T a2) : 
         i0(a0), i1(a1), i2(a2) {};

      bool operator<(triplet t) {
         return i0<t.i0 
            || (i0==t.i0 && i1<t.i1)
            || (i0==t.i0 && i1==t.i1 && i2<t.i2);
      }
};

typedef triplet<int> tripletI;
typedef triplet<double> tripletD;

// declaration of helper functions
void counts(int run, int lumistart, int lumiend, string type, map<string,vector<tripletI> > &cnt, vector<tripletD> &cntref, string hlttype="accept", bool docnt=false, bool doref=true);
lumirange json2lumi(const char *filename);
string human(int num, bool doit);
template<typename T> void fill(vector<triplet<T> > &t, TH1* h, int run, int lumistart, int lumiend, bool docnt=false);
long long int sum(vector<tripletI> t);
long double sum(vector<tripletD> t);
long double sum(vector<tripletI> t, vector<tripletD> tlumi);
set<pair<int,int> > makeset(map<string,vector<tripletI> > themap);
map<pair<int,int>,int> makemap(set<pair<int,int> > theset);
TH1F* makehist(const char* name, vector<tripletI> v, vector<tripletI> v_aux, vector<tripletD> v_ref, map<pair<int,int>,int> themap, bool doprescale, bool hum);
TH1F* makehist_lumi(vector<tripletD> v, map<pair<int,int>,int> themap);
void extrapolate(TH1 *hist);


//////////
// MAIN //
//////////

int main(int argc, const char** argv) {
   if (argc==2 && (string(argv[1]) == "-h" || string(argv[1]) == "--help")) {
      cout << " PURPOSE" << endl;
      cout << " This is a simple program counting the number of events having been recorded for each HLT path, given a JSON file" << endl;
      cout << "" << endl;
      cout << " OPTIONS:" << endl;
      cout << " -h, --help: display the help" << endl;
      cout << " --type some_type: desired counting (some_type must be one of 'Datasets', 'HLT', 'L1T', 'TCDS', 'Streams')" << endl;
      cout << " --hlttype some_hlttype: needed in the case of HLT (some_hlttype must be one of 'accept', 'error', 'pass L1 seed', 'pass prescaler', 'reject', 'avg_prescale')" << endl;
      cout << " --minrun 123456: count starting from this run" << endl;
      cout << " --maxrun 123456: count up to this run" << endl;
      cout << " --human: \"human readable\" output" << endl;
      cout << " --rate: print rates instead of counts" << endl;
      cout << " --time: print total running time in seconds instead of counts" << endl;
      cout << " --json: JSON to use for counting events (default: " << jsonfile << ")" << endl;
      cout << " --basedir: path to the DQM files (default: " << basedir << ")" << endl;
      cout << " --output: path to the output file (default: " << outputfile << ")" << endl;
      cout << " --rebin xx: merge xx bins together in the output file (default: " << rebin << ")" << endl;
      cout << " --scalerate 1000: if >0, scale rates to this target collision rate (in Hz), using the online luminosity (default: " << lumifactor << ")" << endl;
      cout << " --pattern pattern1,pattern2,...: comma-separated list of patterns to match to paths (in the format of TRegexp) (default: " << pattern << ")" << endl;
      cout << " --extrapolate: correct for missing lumi sections" << endl;
      cout << endl;
      cout << "See also https://twiki.cern.ch/twiki/bin/view/CMS/HITriggerTool for more information." << endl;
      return 1;
   }

   // parse options
   int minrun = 0; int maxrun = 999999;
   bool hum = false;

   for (int i=1; i<argc; i++) {
      string arg(argv[i]);

      if (arg=="--human") {hum = true;}
      else if (arg=="--rate") {dorate = true;}
      else if (arg=="--time") {dotime = true;}
      else if (arg=="--type"&&argc>i+1) {i++; theType = argv[i];}
      else if (arg=="--hlttype"&&argc>i+1) {i++; theHlttype = argv[i];}
      else if (arg=="--json"&&argc>i+1) {i++; jsonfile = argv[i];}
      else if (arg=="--basedir"&&argc>i+1) {i++; basedir = argv[i];}
      else if (arg=="--output"&&argc>i+1) {i++; outputfile = argv[i];}
      else if (arg=="--rebin"&&argc>i+1) {i++; rebin = atoi(argv[i]);}
      else if (arg=="--minrun"&&argc>i+1) {i++; minrun = atoi(argv[i]);}
      else if (arg=="--maxrun"&&argc>i+1) {i++; maxrun = atoi(argv[i]);}
      else if (arg=="--scalerate"&&argc>i+1) {i++; lumifactor = magicfactor*atof(argv[i]);}
      else if (arg=="--pattern"&&argc>i+1) {i++; pattern = argv[i];}
      else if (arg=="--extrapolate") {extrapol = true;}
      else cout << "Unsupported option " << argv[i] << endl;
   }

   // produce the vector of TRegexp
   TString tok;
   Ssiz_t from = 0;
   while (pattern.Tokenize(tok, from, ",")) {
      patterns.push_back(TRegexp(tok));
   }

   nooutput = (outputfile == "NONE");

   // check consistency
   if (dorate && dotime) {
      cout << "Error, cannot compute the rate and the time at the same time. Please pick only one of the two flags." << endl;
      return 1;
   }
   if (lumifactor>0) dorate = true;

   if (maxrun <= 285478 && jsonfile == jsonfile_8tev) jsonfile = jsonfile_5tev;
   if (minrun >= 285478 && jsonfile == jsonfile_5tev) jsonfile = jsonfile_8tev;
   if (minrun >= 285478) lumifactor *= magicfactor_8tev / magicfactor_5tev;

   cout << "Will count events by " << theType;
   if (string(theType) == "HLT") cout << ":" << theHlttype;
   cout << endl << "Counting between runs " << minrun << " and " << maxrun << ", according to the JSON file " << jsonfile << endl;
   cout << "Using the DQM files in " << basedir << endl << endl;

   map<string, vector<tripletI> > map_counts;     // main counters
   map<string, vector<tripletI> > map_counts_aux; // used to count lumis (with --rate option) or counts without prescale (with --hlttype avg_prescale)
   vector<tripletD>               v_ref;       // rate of the ref trigger

   // parse the JSON file and extract the list of lumi ranges per run number
   lumirange lumis = json2lumi(jsonfile.Data());

   // for each run, count events
   for (lumirange::iterator it = lumis.begin(); it != lumis.end(); it++) {
      if (it->first<minrun || it->first>maxrun) continue;

      if (dorate) {
         counts(it->first, it->second.first, it->second.second, theType, map_counts, v_ref, theHlttype, false, true);
         counts(it->first, it->second.first, it->second.second, theType, map_counts_aux, v_ref, theHlttype, true, false);
      } else if (theHlttype == "avg_prescale") {
         counts(it->first, it->second.first, it->second.second, theType, map_counts, v_ref, "pass prescaler", false, true);
         counts(it->first, it->second.first, it->second.second, theType, map_counts_aux, v_ref, "pass L1 seed", false, false);
      } else {
         counts(it->first, it->second.first, it->second.second, theType, map_counts, v_ref, theHlttype, dotime);
      }
   }

   // print results

   TFile *f = NULL;
   if (!nooutput) f = new TFile(outputfile.c_str(), "RECREATE");

   cout << "HLT path\t\t" << theType;
   if (theType == "HLT") cout << ":" << theHlttype;
   if (dotime) cout << ": running time [s]";
   if (dorate) cout << ": average rate [Hz]";
   cout << endl;

   // create std::set of pairs of (run,lumi)
   set<pair<int,int> > theset = makeset(map_counts);
   // associate a unique bin number to each (run,lumi) pair
   map<pair<int,int>,int> themap = makemap(theset);

   makehist_lumi(v_ref, themap);

   map<string, vector<tripletI> >::iterator it_nLS = map_counts.begin();
   for (it_nLS = map_counts.begin(); it_nLS != map_counts.end(); it_nLS++) {
      TH1F *hist = makehist(it_nLS->first.c_str(), it_nLS->second, map_counts_aux[it_nLS->first], v_ref, themap, theHlttype == "avg_prescale", hum);
   }


   if (f && f->IsOpen()) {
      f->Write();
      f->Close();
   }

   return 1;
}
// END main



// helper functions

void counts(int run, int lumistart, int lumiend, string type, map<string,vector<tripletI> > &cnt, vector<tripletD> &cntref, string hlttype, bool docnt, bool doref) {
   TString filename = basedir + Form("/DQM_V0001_HLTpb_R000%i.root",run);
   TFile *f = new TFile(filename);
   if (!f->IsOpen()) {
      cout << "Error, could not open " << filename << endl;
      return;
   }
   TString tdirname = Form("DQMData/Run %i/HLT/Run summary/TriggerRates/",run) + TString(type);
   f->cd(tdirname);
   TProfile *hlumi = (TProfile*) f->Get(Form("DQMData/Run %i/HLT/Run summary/LumiMonitoring/lumiVsLS",run));
   if (extrapol) extrapolate(hlumi);

   // if HLT: accept, error, pass L1 seed, pass prescaler, reject

   TIter next(gDirectory->GetListOfKeys());
   TKey *key;
   while ((key = (TKey*)next())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      
      // it must be an histogram
      if (!cl->InheritsFrom("TH1")) continue;
      TH1 *h = (TH1*)key->ReadObj();

      // the name must match one of the requested patterns
      bool match=false; TString hname(h->GetName());
      for (vector<TRegexp>::const_iterator it=patterns.begin(); it!=patterns.end(); it++) {
         if (hname(*it).Length()!=0) {
            match=true;
            break;
         }
      }
      if (!match) continue;

      int nlumis = (lumiend+1-lumistart);

      if (extrapol) extrapolate(h);

      if (type != "HLT") fill(cnt[h->GetName()], h, run, lumistart, lumiend, docnt);
      else {
         string htitle(h->GetTitle());
         if (htitle.find(hlttype) == string::npos) continue;
         else {
            TString thepath; Ssiz_t from=0; TString(htitle).Tokenize(thepath,from," ");
            fill(cnt[thepath.Data()], h, run, lumistart, lumiend, docnt);
         }
      }
   }

   if (doref) {
      fill(cntref, hlumi, run, lumistart, lumiend);
   }

   f->Close();
   delete f;
}

lumirange json2lumi(const char *filename)
{
   lumirange result;

   ifstream jsonfile(filename);
   if (!jsonfile) {
      cout << "Error, could not open " << filename << endl;
      return result;
   }

   ptree pt;
   boost::property_tree::read_json(jsonfile, pt);

   ptree::const_iterator end = pt.end();
   for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
      pair<int, pair<int,int> > element;
      int run;
      int lumi[2];

      run = atoi(it->first.c_str());

      ptree pt2 = (it->second);
      for (ptree::const_iterator it2 = pt2.begin(); it2 != pt2.end(); ++it2) {
         ptree pt3 = (it2->second);
         int i=0;
         for (ptree::const_iterator it3 = pt3.begin(); it3 != pt3.end(); ++it3) {
            lumi[i] = atoi(it3->second.get_value<string>().c_str());
            i++;
            if (i>2) {
               cout << "Error, ill-formatted JSON file " << filename << endl;
               break;
            }
         }
         element.first = run;
         element.second.first = lumi[0];
         element.second.second = lumi[1];
         // cout << run << ": " << lumi[0] << ", " << lumi[1] << endl;
         result.push_back(element);
      }
   }

   return result;
}

string human(int num, bool doit) {
   ostringstream oss;
   if (!doit) oss << num;
   else {
      if (num<1e4) oss << num;
      else if (num<1e7) oss << (int) (num/1e3) << "K";
      else if (num<1e10) oss << (int) (num/1e6) << "M";
      else  oss << (int) (num/1e9) << "G";
   }
   return oss.str();
}

template<typename T> void fill(vector<triplet<T> > &t, TH1* h, int run, int lumistart, int lumiend, bool docnt) {
   if (nooutput) {
      t.push_back(triplet<T>(run,lumistart,docnt ? lumiend-lumistart+1 : h->Integral(lumistart,lumiend)));
   } else {
      for (int i=lumistart; i<=lumiend; i+=rebin) {
         int rebin2 = (i+rebin<=lumiend+1) ? rebin : lumiend-i+1;
         if (docnt || !h) t.push_back(triplet<T>(run,i,lumifactor>0 ? 1 : rebin2));
         else if (i<h->GetNbinsX()) t.push_back(triplet<T>(run,i,h->Integral(i,i+rebin2-1)));
         else t.push_back(triplet<T>(run,i,0));
      }
   }
}

long long int sum(vector<tripletI> t) {
   long long int ans=0;

   for (int i=0; i<t.size(); i++) {
      ans += t[i].i2;
   }

   return ans;
}

long double sum(vector<tripletD> t) {
   long double ans=0;

   for (int i=0; i<t.size(); i++) {
      ans += t[i].i2;
   }

   return ans;
}

long double sum(vector<tripletI> t, vector<tripletD> tlumi) {
   long double ans=0;

   for (int i=0; i<t.size(); i++) {
      double scale = 1.;
      if (lumifactor>0) {
         scale = tlumi[i].i2 > 0 ? lumifactor/tlumi[i].i2 : 0.;
      }
      ans += t[i].i2 * scale;
   }

   return ans;
}

set<pair<int,int> > makeset(map<string,vector<tripletI> > themap) {
   set<pair<int,int> > ans;

   map<string,vector<tripletI> >::const_iterator it;
   for (it=themap.begin(); it!=themap.end(); it++) {
      vector<tripletI>::const_iterator it2;
      for (it2=it->second.begin(); it2!=it->second.end(); it2++) {
         ans.insert(pair<int,int>(it2->i0,it2->i1));
      }
   }

   return ans;
}

map<pair<int,int>,int> makemap(set<pair<int,int> > theset) {
   map<pair<int,int>,int> ans;

   int cnt=1;
   set<pair<int,int> >::const_iterator it;
   for (it=theset.begin(); it!=theset.end(); it++) {
      ans[*it] = cnt;
      cnt++;
   }

   return ans;
}

TH1F* makehist(const char* name, vector<tripletI> v, vector<tripletI> v_aux, vector<tripletD> v_ref, map<pair<int,int>,int> themap, bool doprescale, bool hum) {
   TH1F *hist = NULL;
   if (!nooutput) hist = new TH1F(name,name,themap.size(),1,themap.size());

   set<int> runs;

   if ((dorate || doprescale) && v.size() != v_aux.size()) {
      cout << "different vector sizes for " << name << endl;
      cout << v.size() << " " << v_aux.size() << endl;
      return NULL;
   }
   if (lumifactor>0 && (v.size() != v_ref.size())) {
      cout << "different vector sizes for " << name << endl;
      cout << v.size() << " " << v_aux.size() << " " << v_ref.size() << endl;
      return NULL;
   }

   // fill the histogram
   if (hist) {
      for (int it=0; it<v.size(); it++) {
         int i = themap[pair<int,int>(v[it].i0,v[it].i1)];
         int nint = v[it].i2 + hist->GetBinContent(i-1);
         int n = v[it].i2;
         int n_aux = (dorate || doprescale) ? v_aux[it].i2 : 0;
         double content,error;
         double scale = (lumifactor>0 && v_ref[it].i2>0) ? lumifactor/v_ref[it].i2 : 1.;
         if (dotime) {
            content = lumilength*nint;
            error = 0;
         } else if (dorate) {
            content = n / (lumilength*n_aux);
            error = sqrt(n) / (lumilength*n_aux);
         } else if (doprescale) {
            content = (n>0) ? (double) n_aux / (double) n : 0;
            error = (n>0) ? (n_aux*sqrt(n)+n*sqrt(n_aux))/(n*n) : 0;
         } else {
            content = nint;
            error = sqrt(n);
         }
         hist->SetBinContent(i,content*scale);
         hist->SetBinError(i,error*scale);

         if (runs.find(v[it].i0)==runs.end()) {
            // first time we see this run: label the axis
            hist->GetXaxis()->SetBinLabel(i,Form("%i",v[it].i0));
            runs.insert(v[it].i0);
         } else {
            hist->GetXaxis()->SetBinLabel(i,"");
         }
      }
   }

   // print the summary
   long double thesum = sum(v,v_ref);
   long long int thesum_aux = sum(v_aux);
   if (dotime) {
      if (hist) hist->GetYaxis()->SetTitle("time [s]");
      cout.precision(3);
      cout << name << "\t" << lumilength*thesum << "\t" << endl;
   } else if (dorate) {
      if (hist) hist->GetYaxis()->SetTitle("rate [Hz]");
      cout.precision(3);
      cout << name << "\t" << thesum / (lumilength*thesum_aux) << "\t" << endl;
   } else if (doprescale) {
      if (hist) hist->GetYaxis()->SetTitle("prescale");
      cout.precision(3);
      cout << name << "\t" 
         << ((thesum>0) ? (double) thesum_aux / (double) thesum : 0) 
         << "\t" << endl;
   } else {
      if (hist) hist->GetYaxis()->SetTitle("events");
      cout << name << "\t" << human(thesum,hum) << "\t" << endl;
   }

   return hist;
}

TH1F* makehist_lumi(vector<tripletD> v, map<pair<int,int>,int> themap) {
   TH1F *hist = NULL;
   if (!nooutput) hist = new TH1F("lumi","lumi",themap.size(),1,themap.size());

   set<int> runs;

   // fill the histogram
   if (hist) {
      for (int it=0; it<v.size(); it++) {
         int i = themap[pair<int,int>(v[it].i0,v[it].i1)];
         double n = v[it].i2/1000.;
         double nint = n*lumilength + hist->GetBinContent(i-1);
         double content,error;
         if (dotime || !dorate) {
            content = nint;
            error = 0;
         } else {
            content = n/rebin;
            error = 0;
         }
         hist->SetBinContent(i,content);
         hist->SetBinError(i,error);

         if (runs.find(v[it].i0)==runs.end()) {
            // first time we see this run: label the axis
            hist->GetXaxis()->SetBinLabel(i,Form("%i",v[it].i0));
            runs.insert(v[it].i0);
         } else {
            hist->GetXaxis()->SetBinLabel(i,"");
         }
      }
   }

   // print the summary
   long double thesum = sum(v);
   if (dotime || !dorate) hist->GetYaxis()->SetTitle("Int. lumi. [nb^{-1}]");
   else hist->GetYaxis()->SetTitle("Inst. lumi. [nb^{-1}.s^{-1}]");
   cout.precision(2);
   cout << "Integrated luminosity: " << "\t" << lumilength*thesum/1000. << " nb-1" << endl;

   return hist;
}

void extrapolate(TH1 *hist) {
   int nbins = hist->GetNbinsX();
   for (int i=1; i<nbins; i++) {
      if (hist->GetBinContent(i)==0) {
         // look for the closest non-zero bin
         double k=-1., k1=-1.,k2=-1.;
         for (int j=1; j<=5; j++) {
            if (hist->GetBinContent(i-j)>0) {
               k1 = hist->GetBinContent(i-j);
            }
            if (hist->GetBinContent(i+j)>0) {
               k2 = hist->GetBinContent(i+j);
            }
            if (k1>0 && k2>0) {
               k = (k1+k2)/2.;
               break;
            }
         }
         if (k>0) {
            hist->Fill(hist->GetBinCenter(i),k);
            hist->SetBinContent(i,k);
            hist->SetBinError(i,(k1-k2)/2.);
         }
      }
   }
}
