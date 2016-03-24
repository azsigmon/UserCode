#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPolyLine.h"
#include "TLine.h"
#include "TLatex.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void plotRecHitAna() {

 gStyle->SetOptStat(0);

 TLatex *tx = new TLatex();
 tx->SetTextFont(42);
 tx->SetTextSize(0.04);
 tx->SetNDC(kTRUE);

 TLine *line = new TLine();

 TFile *fin_data = TFile::Open("rechitana_histos_data_262703_vz15.root");
 TFile *fin_hydjet = TFile::Open("rechitana_histos_hydjet_vtxWeights.root");
 TFile *fin_epos = TFile::Open("rechitana_histos_epos.root");

 const int nh = 11;
 int cbins[nh+1] = {0, 10, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200};

 const int neta = 42;
 float etabins[neta+1] = {-5.191, -4.716, -4.363, -4.013, -3.664, -3.314, -2.964, -2.650, -2.322, -2.043, -1.830, -1.653, -1.479, -1.305, -1.131, -0.957, -0.783, -0.609, -0.435, -0.261, -0.087, 0.000, 0.087, 0.261, 0.435, 0.609, 0.783, 0.957, 1.131, 1.305, 1.479, 1.653, 1.830, 2.043, 2.322, 2.650, 2.964, 3.314, 3.664, 4.013, 4.363, 4.716, 5.191};

 int nEv_data[nh+1] = {263712,12385,13187,27406,26206,27247,26430,26035,26201,26493,26170,25952};
 int nEv_hydjet[nh+1] = {11730,561,633,1143,1191,1176,1140,1191,1210,1149,1200,1136};
 int nEv_epos[nh+1] = {59988,3178,2990,5979,5980,5981,5979,5981,5979,5980,5980,5981};

 TH1F *dEtdeta_data[nh+1];
 TH1F *dEtdeta_hydjet[nh+1];
 TH1F *dEtdeta_epos[nh+1];
 TH1F *ratio[nh+1];
 TH1F *ratio2[nh+1];

 dEtdeta_data[0] = (TH1F*)fin_data->Get("dEtadeta_0_100");
 dEtdeta_hydjet[0] = (TH1F*)fin_hydjet->Get("dEtadeta_0_100");
 dEtdeta_epos[0] = (TH1F*)fin_epos->Get("dEtadeta_0_100");

 for(int i = 0; i < nh; i++) {
   dEtdeta_data[i+1] = (TH1F*)fin_data->Get(Form("dEtadeta_%d_%d",cbins[i]/2,cbins[i+1]/2));
   dEtdeta_hydjet[i+1] = (TH1F*)fin_hydjet->Get(Form("dEtadeta_%d_%d",cbins[i]/2,cbins[i+1]/2));
   dEtdeta_epos[i+1] = (TH1F*)fin_epos->Get(Form("dEtadeta_%d_%d",cbins[i]/2,cbins[i+1]/2));
 }

 for(int i = 0; i < nh+1; i++) {
   dEtdeta_data[i]->Scale(1/(double)nEv_data[i]);
   dEtdeta_hydjet[i]->Scale(1/(double)nEv_hydjet[i]);
   dEtdeta_hydjet[i]->GetYaxis()->SetTitle("1/N_{ev} dE_{T}/d#eta");
   dEtdeta_hydjet[i]->SetLineColor(kRed);
   dEtdeta_epos[i]->Scale(1/(double)nEv_epos[i]);
   dEtdeta_epos[i]->GetYaxis()->SetTitle("1/N_{ev} dE_{T}/d#eta");
   dEtdeta_epos[i]->SetLineColor(kGreen+2);
   ratio[i] = new TH1F(Form("ratioHydjet_%d",i),";#eta;Data / Hydjet",neta,etabins);
   ratio[i]->Divide(dEtdeta_data[i], dEtdeta_hydjet[i], 1, 1);
   ratio[i]->GetYaxis()->SetRangeUser(0.0,1.4);
   ratio[i]->SetMarkerColor(kRed);
   ratio[i]->SetLineColor(kRed);
   ratio2[i] = new TH1F(Form("ratioEpos_%d",i),";#eta;Data / Epos",neta,etabins);
   ratio2[i]->Divide(dEtdeta_data[i], dEtdeta_epos[i], 1, 1);
   ratio2[i]->GetYaxis()->SetRangeUser(0.8,2.2);
   ratio2[i]->SetMarkerColor(kGreen+2);
   ratio2[i]->SetLineColor(kGreen+2);
 }

 TFile *outf = new TFile("energyflow_histos_vz.root","recreate");
 outf->cd();

 dEtdeta_data[0]->SetName("dEtdeta_data_0_100"); dEtdeta_data[0]->Write();
 dEtdeta_hydjet[0]->SetName("dEtdeta_Hydjet_0_100"); dEtdeta_hydjet[0]->Write();
 ratio[0]->SetName("ratioHydjet_0_100"); ratio[0]->Write();
 for(int i = 0; i < nh-1; i++) {
   dEtdeta_data[i+1]->SetName(Form("dEtdeta_data_%d_%d",cbins[i]/2,cbins[i+1]/2));
   dEtdeta_data[i+1]->Write();
   dEtdeta_hydjet[i+1]->SetName(Form("dEtdeta_Hydjet_%d_%d",cbins[i]/2,cbins[i+1]/2));
   dEtdeta_hydjet[i+1]->Write();
   ratio[i+1]->SetName(Form("ratioHydjet_%d_%d",cbins[i]/2,cbins[i+1]/2));
   ratio[i+1]->Write();
   ratio2[i+1]->SetName(Form("ratioEpos_%d_%d",cbins[i]/2,cbins[i+1]/2));
 }

 outf->Close();

 TLegend *l1 = new TLegend(0.4,0.75,0.7,0.9);
 l1->SetBorderSize(0);
 l1->SetFillStyle(0);
 l1->SetTextFont(42);
 l1->SetTextSize(0.04);
 l1->AddEntry(dEtdeta_data[0],"Run 262548","lp");
 l1->AddEntry(dEtdeta_hydjet[0],"Hydjet","l");
 l1->AddEntry(dEtdeta_epos[0],"Epos","l");

 for(int i = 0; i < nh+1; i++) {

   TCanvas *c1 = new TCanvas();
   dEtdeta_hydjet[i]->Draw("hist");
   dEtdeta_epos[i]->Draw("hist same");
   dEtdeta_data[i]->Draw("ep same");
   l1->Draw();

   if(i==0) tx->DrawLatex(0.13,0.95,"0-100% centrality, tower E_{T} > 0.2 GeV");
   else tx->DrawLatex(0.13,0.95,Form("%d-%d%% centrality, tower E_{T} > 0.2 GeV",(i-1)*10,i*10));

   //if(i==0) c1->SaveAs("figs/dEtdeta_all_5Dec.png");
   //else c1->SaveAs(Form("figs/dEtdeta_%d_%d_5Dec.png",(i-1)*10,i*10));

   TCanvas *c2 = new TCanvas("c2","c2",600,300);
   ratio[i]->Draw("ep");
   line->DrawLine(-6,1,6,1);

   //if(i==0) c2->SaveAs("figs/ratio_hydjet_all_5Dec.png");
   //else c2->SaveAs(Form("figs/ratio_hydjet_%d_%d_5Dec.png",(i-1)*10,i*10));

   TCanvas *c3 = new TCanvas("c3","c3",600,300);
   ratio2[i]->Draw("ep");
   line->DrawLine(-6,1,6,1);

   //if(i==0) c3->SaveAs("figs/ratio_epos_all_5Dec.png");
   //else c3->SaveAs(Form("figs/ratio_epos_%d_%d_5Dec.png",(i-1)*10,i*10));

 }

}
