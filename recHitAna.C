#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLorentzVector.h"
#include "TLegend.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define PI 3.14159265

void recHitAna(TString infilename="/afs/cern.ch/user/a/azsigmon/eos/cms/store/group/phys_heavyions/velicanu/forest/HIRun2015/HIMinimumBias2/Merged/HiForestPromptReco_262703.root", TString outfilename="rechitana_histos_data_262703_vz15.root", const bool isMC = false) {

//void recHitAna(TString infilename="/afs/cern.ch/work/y/ygo/public/centrality/Hydjet_Quenched_MinBias_5020GeV_755p4.root", TString outfilename="rechitana_histos_hydjet_vtxWeights.root", const bool isMC = true) {

//void recHitAna(TString infilename="~/eos/cms/store/group/phys_heavyions/azsigmon/PbPb2015/HiForest_Epos_merged_60k_v1.root", TString outfilename="rechitana_histos_epos.root", const bool isMC = true) {

const int binNum = 200;
const float bins[binNum+1] = {0, 2.72984, 2.98692, 3.25167, 3.61242, 4.06252, 4.56618, 5.14055, 5.70672, 6.32708, 6.9324, 7.56096, 8.20876, 8.88655, 9.59544, 10.3374, 11.0813, 11.9498, 12.8319, 13.6498, 14.5888, 15.5605, 16.6097, 17.7503, 18.9464, 20.2978, 21.6428, 23.0418, 24.5564, 26.1153, 27.8125, 29.4227, 31.2841, 33.2305, 35.443, 37.3632, 39.4451, 41.6987, 44.1925, 46.5716, 48.9, 51.3237, 53.988, 56.7292, 59.4536, 62.4428, 65.4692, 68.2821, 71.1936, 74.4321, 77.7686, 81.0463, 84.8161, 88.5267, 92.2663, 96.6656, 101.351, 105.285, 110.117, 114.816, 119.567, 124.529, 129.938, 135.671, 140.838, 146.703, 152.594, 158.517, 164.975, 171.343, 177.728, 184.546, 191.244, 198.446, 205.108, 213.316, 220.599, 228.315, 236.281, 244.342, 252.45, 261.633, 269.583, 279.559, 288.2, 297.737, 306.055, 315.983, 327.045, 337.749, 346.894, 358.48, 369.485, 381.664, 393.576, 405.478, 417.286, 430.413, 443.847, 459.049, 472.315, 487.009, 500.188, 515.293, 531.583, 544.335, 558.209, 573.449, 588.329, 605.822, 622.205, 640.538, 656.491, 671.834, 688.743, 706.301, 724.13, 742.685, 760.619, 778.073, 799.12, 819.481, 840.666, 862.68, 882.684, 904.961, 927.323, 949.152, 973.167, 997.165, 1019.45, 1041.74, 1065.03, 1090.72, 1119.97, 1147.18, 1174.32, 1201.02, 1227.46, 1257.01, 1285.99, 1318.23, 1349.45, 1380.86, 1417.6, 1449.57, 1482.72, 1519.54, 1553.7, 1589.98, 1627.66, 1666.3, 1703.92, 1740.4, 1772.18, 1814.64, 1855.89, 1899.62, 1940.76, 1986.66, 2031.36, 2074.46, 2123.35, 2175.54, 2227.21, 2279.54, 2329.45, 2384.78, 2439.72, 2497.71, 2552.48, 2613.1, 2670.02, 2731.11, 2791.89, 2851.2, 2915.49, 2980.99, 3051.15, 3118.76, 3186.04, 3260.17, 3337.62, 3423.49, 3500.23, 3578.98, 3660.17, 3743.73, 3830.48, 3920.57, 4026.55, 4129.73, 4225.15, 4337.4, 4449.95, 4569.9, 4693.32, 4841.35, 5002.22, 5222.89, 10000000}; //Epos

 TH1::SetDefaultSumw2();

 TFile * outf = new TFile(outfilename,"recreate");

 TFile * inf = TFile::Open(infilename);

 /*TTree * tgen;
 int mult;
 vector<float> *pt; vector<float> *eta; vector<float> *phi;
 int pdg[10000]; int chg[10000];
 if(isMC) {
  tgen = (TTree *) inf->Get("HiGenParticleAna/hi"); 
  tgen->SetBranchAddress("mult", &mult);
  tgen->SetBranchAddress("pt", &pt);
  tgen->SetBranchAddress("eta", &eta);
  tgen->SetBranchAddress("phi", &phi);
  tgen->SetBranchAddress("pdg", pdg);
  tgen->SetBranchAddress("chg", chg);
 }*/

 TTree * tskim = (TTree *) inf->Get("skimanalysis/HltTree");
 int phfCoincFilter3; tskim->SetBranchAddress("phfCoincFilter3", &phfCoincFilter3);
 int pprimaryVertexFilter; tskim->SetBranchAddress("pprimaryVertexFilter", &pprimaryVertexFilter);

 TTree * thlt  = (TTree *) inf->Get("hltanalysis/HltTree");
 int HLT_HIL1MinimumBiasHF1AND_v1; thlt->SetBranchAddress("HLT_HIL1MinimumBiasHF1AND_v1", &HLT_HIL1MinimumBiasHF1AND_v1);
 int HLT_HIL1MinimumBiasHF1ANDExpress_v1; thlt->SetBranchAddress("HLT_HIL1MinimumBiasHF1ANDExpress_v1", &HLT_HIL1MinimumBiasHF1ANDExpress_v1);

 TTree *ttower = (TTree *) inf->Get("rechitanalyzer/tower");
 int   nTow; 		ttower->SetBranchAddress("n", &nTow);
 float etaTow[10000];   ttower->SetBranchAddress("eta", etaTow);
 float etTow[10000]; 	ttower->SetBranchAddress("et", etTow);

 TTree * teven = (TTree *) inf->Get("hiEvtAnalyzer/HiTree");
 int hiBin;		teven->SetBranchAddress("hiBin", &hiBin);
 float hiHF;		teven->SetBranchAddress("hiHF", &hiHF);
 float vz;		teven->SetBranchAddress("vz", &vz);

 TFile * fileVertex = new TFile("vertexWeighting.root");
 TH1F * vertexWeight = (TH1F*) fileVertex->Get("vz_weight");

 //Defining histos
 const int nh = 11;
 int cbins[nh+1] = {0, 10, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200};

 const int neta = 42;
 float etabins[neta+1] = {-5.191, -4.716, -4.363, -4.013, -3.664, -3.314, -2.964, -2.650, -2.322, -2.043, -1.830, -1.653, -1.479, -1.305, -1.131, -0.957, -0.783, -0.609, -0.435, -0.261, -0.087, 0.000, 0.087, 0.261, 0.435, 0.609, 0.783, 0.957, 1.131, 1.305, 1.479, 1.653, 1.830, 2.043, 2.322, 2.650, 2.964, 3.314, 3.664, 4.013, 4.363, 4.716, 5.191};

 TH1F *dEtdeta[nh+1];
 dEtdeta[0] = new TH1F("dEtadeta_0_100",";#eta;dE_{T}/d#eta",neta,etabins);

 for(int i=0; i<nh; i++) {
   dEtdeta[i+1] = new TH1F(Form("dEtadeta_%d_%d",cbins[i]/2,cbins[i+1]/2),";#eta;dE_{T}/d#eta",neta,etabins);
 }

 TH1F *hBin = new TH1F("centralityBin",";centrality bin;Events",200,0,200);

 int nEv[nh+1] = {0};

 //Event loop
 for(int iev = 0; iev < ttower->GetEntries(); iev++) {

   if(iev%2000 == 0) cout << "Processing event: " << iev << endl;
   tskim->GetEntry(iev);
   thlt->GetEntry(iev);
   teven->GetEntry(iev);
   ttower->GetEntry(iev);
   //if(isMC) tgen->GetEntry(iev);

   if(fabs(vz) > 15.0) continue;
   if(!isMC && (!pprimaryVertexFilter || !phfCoincFilter3 || !HLT_HIL1MinimumBiasHF1AND_v1)) continue;
   //if(!isMC && (!pprimaryVertexFilter || !phfCoincFilter3 || !HLT_HIL1MinimumBiasHF1ANDExpress_v1)) continue;

   nEv[0]++;

   /*int hiBin_new = 200;
   for(Int_t iter = 0; iter < binNum; iter++) {
      if(hiHF >= bins[iter] && hiHF < bins[iter+1]) {
        hiBin_new = 199 - iter;
        break;
      }
   }*/

   int b=-1;
   for(int i=0; i<nh; i++) {
     if(hiBin>=cbins[i] && hiBin<cbins[i+1]) b=i+1;
     //if(hiBin_new>=cbins[i] && hiBin_new<cbins[i+1]) b=i+1;
   }

   if(b<0) { cout << "*"; continue; }

   nEv[b]++;

   hBin->Fill(hiBin);
   //hBin->Fill(hiBin_new);

   float weight = 1;
   if(isMC) weight = vertexWeight->GetBinContent(vertexWeight->FindBin(vz));

   for(int it=0; it<nTow; it++) {

     if(etTow[it]<0.2) continue;
     dEtdeta[0]->Fill(etaTow[it],etTow[it]*weight);
     dEtdeta[b]->Fill(etaTow[it],etTow[it]*weight);

   }

 }

 outf->cd();
 cout << endl;
 for(int i=0; i<nh+1; i++) {
   cout << nEv[i] << ",";
   dEtdeta[i]->Write();
 }
 cout << endl;
 hBin->Write();
 outf->Write();
 outf->Close();

}
