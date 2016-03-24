{

 gSystem->Load("libFWCoreFWLite");
 gSystem->Load("libDataFormatsFWLite");
 gSystem->Load("libDataFormatsCommon");
 gSystem->Load("libDataFormatsCaloTowers");
 gSystem->Load("libDataFormatsHeavyIonEvent");
 gSystem->Load("libSimDataFormatsHiGenData");
 gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
 gSystem->AddIncludePath("-I$CMSSW_RELEASE_BASE/src/");

 FWLiteEnabler::enable();

 gSystem->Load("libRooFit") ;
 using namespace RooFit ;

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);

  gStyle->SetTitleFillColor(0);
  gStyle->SetStatColor(0);

  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameLineColor(kBlack);

  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasBorderSize(0);

  gStyle->SetPadColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(0);

  gStyle->SetTextSize(0.04);
  gStyle->SetTextFont(42);
  gStyle->SetLabelFont(42,"xyz");
  gStyle->SetTitleFont(42,"xyz");
  gStyle->SetTitleSize(0.05,"xyz");
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadRightMargin(0.07);
  gStyle->SetPadLeftMargin(0.12);

  gStyle->SetTitleXOffset(1.1);
  gStyle->SetTitleYOffset(1.2);

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  gStyle->SetCanvasDefH(600);
  gStyle->SetCanvasDefW(600);

  gStyle->SetStatX(0.35);
  gStyle->SetStatY(0.92);

  //gStyle->SetHistMinimumZero(kTRUE);

  //gStyle->SetErrorX(0); //disable if you want to draw horizontal error bars, e.g. when having variable bin size
  gStyle->SetEndErrorSize(1);

  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1);

  gROOT->ForceStyle();

 cout << "loaded" << endl;
}
