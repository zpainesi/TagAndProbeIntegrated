/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// This script is for computing the plotting the pre-/post-firing rates for EG, Taus, Muons, Jets      //
// 				 ( -> see objects cuts at the end <- )				       //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <sys/stat.h>
#include <stdio.h>
#include "TCanvas.h"
#include "TH1F.h"
#include <iostream>

bool draw_eg=true;
bool save_canvas=true;  // whether the drawing canvases will be saved
bool create_histos_root_file=true;

Int_t L1_bit_eg[506];


void create_prefiring_plots_eg(TString fIn, TString outFile, TString dataset, TString era_paveCMS, int Run2or3) //e.g. dataset=EphZB_Run2023C // 
Run2or3= 2/3
{		//outfile: Timing_EG2024B.root   // era_paveCMS: 2024B

if(save_canvas)
{
	TString directoryName = "../plots/"+dataset;
	int result = mkdir(directoryName, 0777);
	TString directoryName_2 = "../plots/"+dataset+"/others";
	int result2 = mkdir(directoryName_2, 0777);
}

TString energy_CoM="13.6";
if(Run2or3==2)energy_CoM="13";
if(outFile=="")std::cout<<std::endl<<"Output file will not be created . . ."<<std::endl<<std::endl;
if(outFile=="" && create_histos_root_file==true)
{
	std::cout<<std::endl<<"Output file name is empty . . ."<<std::endl;
	//return(0);
}
// Histos definition
TH1I *histo_eg_BX_cut1=new TH1I("","",5,-2.5,2.5);
TH1I *histo_eg_BX_cut1_unpref=new TH1I("","",5,-2.5,2.5);
TH1I *histo_eg_BX_l1Cut=new TH1I("","",5,-2.5,2.5);
TH1I *histo_eg_BX_l1Cut_unpref=new TH1I("","",5,-2.5,2.5);
TH1I *histo_eg_BX_L1FinalOR=new TH1I("","",5,-2.5,2.5);
TH1I *histo_eg_BX_L1FinalOR_unpref=new TH1I("","",5,-2.5,2.5);

histo_eg_BX_cut1->SetStats(0);
histo_eg_BX_cut1_unpref->SetStats(0);
histo_eg_BX_l1Cut->SetStats(0);
histo_eg_BX_l1Cut_unpref->SetStats(0);
histo_eg_BX_L1FinalOR->SetStats(0);
histo_eg_BX_L1FinalOR_unpref->SetStats(0);

// Histos, one for each BX
TH1D *histo_eg_eta_cut1[5], *histo_eg_eta_cut1_unpref[5], *histo_eg_eta_l1Cut[5], *histo_eg_eta_l1Cut_unpref[5], *histo_eg_eta_L1FinalOR[5], *histo_eg_eta_L1FinalOR_unpref[5];
TH1D *histo_eg_pt_cut1[5], *histo_eg_pt_cut1_unpref[5], *histo_eg_pt_l1Cut[5], *histo_eg_pt_l1Cut_unpref[5], *histo_eg_pt_L1FinalOR[5],*histo_eg_pt_L1FinalOR_unpref[5];

// Rate histos, 0 for pre - 1 for post
TH1D *rate_vs_eta_eg_cut1[2], *rate_vs_eta_eg_cut1_num[2], *rate_vs_eta_eg_cut1_den[2];
TH1D *rate_vs_pt_eg_cut1[2], *rate_vs_pt_eg_cut1_num[2], *rate_vs_pt_eg_cut1_den[2];
TH1D *rate_vs_eta_eg_cut1_unpref[2], *rate_vs_eta_eg_cut1_unpref_num[2], *rate_vs_eta_eg_cut1_unpref_den[2];
TH1D *rate_vs_pt_eg_cut1_unpref[2], *rate_vs_pt_eg_cut1_unpref_num[2], *rate_vs_pt_eg_cut1_unpref_den[2];

TH1D *rate_vs_eta_eg_l1Cut[2], *rate_vs_eta_eg_l1Cut_num[2], *rate_vs_eta_eg_l1Cut_den[2];
TH1D *rate_vs_pt_eg_l1Cut[2], *rate_vs_pt_eg_l1Cut_num[2], *rate_vs_pt_eg_l1Cut_den[2];
TH1D *rate_vs_eta_eg_l1Cut_unpref[2], *rate_vs_eta_eg_l1Cut_unpref_num[2], *rate_vs_eta_eg_l1Cut_unpref_den[2];
TH1D *rate_vs_pt_eg_l1Cut_unpref[2], *rate_vs_pt_eg_l1Cut_unpref_num[2], *rate_vs_pt_eg_l1Cut_unpref_den[2];

TH1D *rate_vs_eta_eg_L1FinalOR[2], *rate_vs_eta_eg_L1FinalOR_num[2], *rate_vs_eta_eg_L1FinalOR_den[2];
TH1D *rate_vs_pt_eg_L1FinalOR[2], *rate_vs_pt_eg_L1FinalOR_num[2], *rate_vs_pt_eg_L1FinalOR_den[2];
TH1D *rate_vs_eta_eg_L1FinalOR_unpref[2], *rate_vs_eta_eg_L1FinalOR_unpref_num[2], *rate_vs_eta_eg_L1FinalOR_unpref_den[2];
TH1D *rate_vs_pt_eg_L1FinalOR_unpref[2], *rate_vs_pt_eg_L1FinalOR_unpref_num[2], *rate_vs_pt_eg_L1FinalOR_unpref_den[2];


TH2D *map_eta_phi_eg_cut1[2], *map_eta_phi_eg_cut1_unpref[2],*map_eta_phi_eg_l1Cut[2], *map_eta_phi_eg_l1Cut_unpref[2], *map_eta_phi_eg_L1FinalOR[2], *map_eta_phi_eg_L1FinalOR_unpref[2];

const Int_t XBINSeg = 6;
Double_t xEdgesEg[XBINSeg + 1] = {10.,20.,30.,50.,100.,300.,1000.};


for(int i=0; i<5; i++)
{
	histo_eg_eta_cut1[i]=new TH1D("","",60,-3.,3.);
	histo_eg_pt_cut1[i]=new TH1D("","",XBINSeg,xEdgesEg);
	histo_eg_eta_cut1[i]->Sumw2();
	histo_eg_eta_cut1[i]->SetStats(0);
	histo_eg_pt_cut1[i]->Sumw2();
        histo_eg_pt_cut1[i]->SetStats(0);

	histo_eg_eta_cut1_unpref[i]=new TH1D("","",60,-3.,3.);
        histo_eg_pt_cut1_unpref[i]=new TH1D("","",XBINSeg,xEdgesEg);
        histo_eg_eta_cut1_unpref[i]->Sumw2();
        histo_eg_eta_cut1_unpref[i]->SetStats(0);
        histo_eg_pt_cut1_unpref[i]->Sumw2();
        histo_eg_pt_cut1_unpref[i]->SetStats(0);

	histo_eg_eta_l1Cut[i]=new TH1D("","",60,-3.,3.);
        histo_eg_pt_l1Cut[i]=new TH1D("","",XBINSeg,xEdgesEg);
        histo_eg_eta_l1Cut[i]->Sumw2();
        histo_eg_eta_l1Cut[i]->SetStats(0);
        histo_eg_pt_cut1[i]->Sumw2();
        histo_eg_pt_cut1[i]->SetStats(0);

	histo_eg_eta_l1Cut_unpref[i]=new TH1D("","",60,-3.,3.);
        histo_eg_pt_l1Cut_unpref[i]=new TH1D("","",XBINSeg,xEdgesEg);
        histo_eg_eta_l1Cut_unpref[i]->Sumw2();
        histo_eg_eta_l1Cut_unpref[i]->SetStats(0);
        histo_eg_pt_l1Cut_unpref[i]->Sumw2();
        histo_eg_pt_l1Cut_unpref[i]->SetStats(0);

	histo_eg_eta_L1FinalOR[i] = new TH1D("", "", 60, -3., 3.);
	histo_eg_pt_L1FinalOR[i] = new TH1D("", "", XBINSeg, xEdgesEg);
	histo_eg_eta_L1FinalOR[i]->Sumw2();
	histo_eg_eta_L1FinalOR[i]->SetStats(0);
	histo_eg_pt_L1FinalOR[i]->Sumw2();
	histo_eg_pt_L1FinalOR[i]->SetStats(0);

	histo_eg_eta_L1FinalOR_unpref[i] = new TH1D("", "", 60, -3., 3.);
	histo_eg_pt_L1FinalOR_unpref[i] = new TH1D("", "", XBINSeg, xEdgesEg);
	histo_eg_eta_L1FinalOR_unpref[i]->Sumw2();
	histo_eg_eta_L1FinalOR_unpref[i]->SetStats(0);
	histo_eg_pt_L1FinalOR_unpref[i]->Sumw2();
	histo_eg_pt_L1FinalOR_unpref[i]->SetStats(0);

	if(i<2)
	{
		rate_vs_eta_eg_cut1[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_cut1_num[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_cut1_den[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_cut1[i]->Sumw2();
		rate_vs_eta_eg_cut1_num[i]->Sumw2();
		rate_vs_eta_eg_cut1_den[i]->Sumw2();
		rate_vs_eta_eg_cut1[i]->SetStats(0);
		rate_vs_eta_eg_cut1_num[i]->SetStats(0);
		rate_vs_eta_eg_cut1_den[i]->SetStats(0);
		map_eta_phi_eg_cut1[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_eg_cut1[i]->SetStats(0);
		map_eta_phi_eg_cut1[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_eg_cut1[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_eg_cut1[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_cut1[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_cut1[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_eg_cut1[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_eg_cut1[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_eg_cut1[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_eg_cut1[i]->SetStats(0);
		rate_vs_pt_eg_cut1[i]=new TH1D("","",XBINSeg,xEdgesEg);
                rate_vs_pt_eg_cut1_num[i]=new TH1D("","",XBINSeg,xEdgesEg);
                rate_vs_pt_eg_cut1_den[i]=new TH1D("","",XBINSeg,xEdgesEg);
                rate_vs_pt_eg_cut1[i]->Sumw2();
                rate_vs_pt_eg_cut1_num[i]->Sumw2();
                rate_vs_pt_eg_cut1_den[i]->Sumw2();
		rate_vs_pt_eg_cut1[i]->SetStats(0);
                rate_vs_pt_eg_cut1_num[i]->SetStats(0);
                rate_vs_pt_eg_cut1_den[i]->SetStats(0);

                rate_vs_eta_eg_cut1_unpref[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_cut1_unpref_num[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_cut1_unpref_den[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_cut1_unpref[i]->Sumw2();
		rate_vs_eta_eg_cut1_unpref_num[i]->Sumw2();
		rate_vs_eta_eg_cut1_unpref_den[i]->Sumw2();
		rate_vs_eta_eg_cut1_unpref[i]->SetStats(0);
		rate_vs_eta_eg_cut1_unpref_num[i]->SetStats(0);
		rate_vs_eta_eg_cut1_unpref_den[i]->SetStats(0);
		map_eta_phi_eg_cut1_unpref[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_eg_cut1_unpref[i]->SetStats(0);
		map_eta_phi_eg_cut1_unpref[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_eg_cut1_unpref[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_eg_cut1_unpref[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_cut1_unpref[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_cut1_unpref[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_eg_cut1_unpref[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_eg_cut1_unpref[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_eg_cut1_unpref[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_eg_cut1_unpref[i]->SetStats(0);
		rate_vs_pt_eg_cut1_unpref[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_cut1_unpref_num[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_cut1_unpref_den[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_cut1_unpref[i]->Sumw2();
		rate_vs_pt_eg_cut1_unpref_num[i]->Sumw2();
		rate_vs_pt_eg_cut1_unpref_den[i]->Sumw2();
		rate_vs_pt_eg_cut1_unpref[i]->SetStats(0);
		rate_vs_pt_eg_cut1_unpref_num[i]->SetStats(0);
		rate_vs_pt_eg_cut1_unpref_den[i]->SetStats(0);

                rate_vs_eta_eg_l1Cut[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_l1Cut_num[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_l1Cut_den[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_l1Cut[i]->Sumw2();
		rate_vs_eta_eg_l1Cut_num[i]->Sumw2();
		rate_vs_eta_eg_l1Cut_den[i]->Sumw2();
		rate_vs_eta_eg_l1Cut[i]->SetStats(0);
		rate_vs_eta_eg_l1Cut_num[i]->SetStats(0);
		rate_vs_eta_eg_l1Cut_den[i]->SetStats(0);
		map_eta_phi_eg_l1Cut[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_eg_l1Cut[i]->SetStats(0);
		map_eta_phi_eg_l1Cut[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_eg_l1Cut[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_eg_l1Cut[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_l1Cut[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_l1Cut[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_eg_l1Cut[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_eg_l1Cut[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_eg_l1Cut[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_eg_l1Cut[i]->SetStats(0);
		rate_vs_pt_eg_l1Cut[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_l1Cut_num[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_l1Cut_den[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_l1Cut[i]->Sumw2();
		rate_vs_pt_eg_l1Cut_num[i]->Sumw2();
		rate_vs_pt_eg_l1Cut_den[i]->Sumw2();
		rate_vs_pt_eg_l1Cut[i]->SetStats(0);
		rate_vs_pt_eg_l1Cut_num[i]->SetStats(0);
		rate_vs_pt_eg_l1Cut_den[i]->SetStats(0);

		rate_vs_eta_eg_l1Cut_unpref[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_l1Cut_unpref_num[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_l1Cut_unpref_den[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_l1Cut_unpref[i]->Sumw2();
		rate_vs_eta_eg_l1Cut_unpref_num[i]->Sumw2();
		rate_vs_eta_eg_l1Cut_unpref_den[i]->Sumw2();
		rate_vs_eta_eg_l1Cut_unpref[i]->SetStats(0);
		rate_vs_eta_eg_l1Cut_unpref_num[i]->SetStats(0);
		rate_vs_eta_eg_l1Cut_unpref_den[i]->SetStats(0);
		map_eta_phi_eg_l1Cut_unpref[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_eg_l1Cut_unpref[i]->SetStats(0);
		map_eta_phi_eg_l1Cut_unpref[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_eg_l1Cut_unpref[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_eg_l1Cut_unpref[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_l1Cut_unpref[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_l1Cut_unpref[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_eg_l1Cut_unpref[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_eg_l1Cut_unpref[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_eg_l1Cut_unpref[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_eg_l1Cut_unpref[i]->SetStats(0);
		rate_vs_pt_eg_l1Cut_unpref[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_l1Cut_unpref_num[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_l1Cut_unpref_den[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_l1Cut_unpref[i]->Sumw2();
		rate_vs_pt_eg_l1Cut_unpref_num[i]->Sumw2();
		rate_vs_pt_eg_l1Cut_unpref_den[i]->Sumw2();
		rate_vs_pt_eg_l1Cut_unpref[i]->SetStats(0);
		rate_vs_pt_eg_l1Cut_unpref_num[i]->SetStats(0);
		rate_vs_pt_eg_l1Cut_unpref_den[i]->SetStats(0);

		rate_vs_eta_eg_L1FinalOR[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_L1FinalOR_num[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_L1FinalOR_den[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_L1FinalOR[i]->Sumw2();
		rate_vs_eta_eg_L1FinalOR_num[i]->Sumw2();
		rate_vs_eta_eg_L1FinalOR_den[i]->Sumw2();
		rate_vs_eta_eg_L1FinalOR[i]->SetStats(0);
		rate_vs_eta_eg_L1FinalOR_num[i]->SetStats(0);
		rate_vs_eta_eg_L1FinalOR_den[i]->SetStats(0);
		map_eta_phi_eg_L1FinalOR[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_eg_L1FinalOR[i]->SetStats(0);
		map_eta_phi_eg_L1FinalOR[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_eg_L1FinalOR[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_eg_L1FinalOR[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_L1FinalOR[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_L1FinalOR[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_eg_L1FinalOR[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_eg_L1FinalOR[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_eg_L1FinalOR[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_eg_L1FinalOR[i]->SetStats(0);
		rate_vs_pt_eg_L1FinalOR[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_L1FinalOR_num[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_L1FinalOR_den[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_L1FinalOR[i]->Sumw2();
		rate_vs_pt_eg_L1FinalOR_num[i]->Sumw2();
		rate_vs_pt_eg_L1FinalOR_den[i]->Sumw2();
		rate_vs_pt_eg_L1FinalOR[i]->SetStats(0);
		rate_vs_pt_eg_L1FinalOR_num[i]->SetStats(0);
		rate_vs_pt_eg_L1FinalOR_den[i]->SetStats(0);

		rate_vs_eta_eg_L1FinalOR_unpref[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_L1FinalOR_unpref_num[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_L1FinalOR_unpref_den[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_L1FinalOR_unpref[i]->Sumw2();
		rate_vs_eta_eg_L1FinalOR_unpref_num[i]->Sumw2();
		rate_vs_eta_eg_L1FinalOR_unpref_den[i]->Sumw2();
		rate_vs_eta_eg_L1FinalOR_unpref[i]->SetStats(0);
		rate_vs_eta_eg_L1FinalOR_unpref_num[i]->SetStats(0);
		rate_vs_eta_eg_L1FinalOR_unpref_den[i]->SetStats(0);
		map_eta_phi_eg_L1FinalOR_unpref[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_eg_L1FinalOR_unpref[i]->SetStats(0);
		map_eta_phi_eg_L1FinalOR_unpref[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_eg_L1FinalOR_unpref[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_eg_L1FinalOR_unpref[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_L1FinalOR_unpref[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_L1FinalOR_unpref[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_eg_L1FinalOR_unpref[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_eg_L1FinalOR_unpref[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_eg_L1FinalOR_unpref[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_eg_L1FinalOR_unpref[i]->SetStats(0);
		rate_vs_pt_eg_L1FinalOR_unpref[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_L1FinalOR_unpref_num[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_L1FinalOR_unpref_den[i]=new TH1D("","",XBINSeg,xEdgesEg);
		rate_vs_pt_eg_L1FinalOR_unpref[i]->Sumw2();
		rate_vs_pt_eg_L1FinalOR_unpref_num[i]->Sumw2();
		rate_vs_pt_eg_L1FinalOR_unpref_den[i]->Sumw2();
		rate_vs_pt_eg_L1FinalOR_unpref[i]->SetStats(0);
		rate_vs_pt_eg_L1FinalOR_unpref_num[i]->SetStats(0);
		rate_vs_pt_eg_L1FinalOR_unpref_den[i]->SetStats(0);

	}
}

// Input file
TFile *fin=new TFile( fIn , "READ"); 

// Trees, branches & variables definition
TTree *EG=(TTree*)fin->Get("ZeroBias_Timing/EG");

float egPt,egEta, egPhi, l1tEgPt, l1tEgEta, l1tEgPhi;
Int_t l1tEgQual, l1tEgIso,  l1tEgBx, isUnprefirableEventEg, RunNumberEg;
ULong64_t EventNumberEg;
Bool_t L1FinalOReg;

EG->SetBranchAddress("RunNumber", &RunNumberEg);
EG->SetBranchAddress("EventNumber",&EventNumberEg);
EG->SetBranchAddress("l1tEgPt",&l1tEgPt);
EG->SetBranchAddress("l1tEgEta",&l1tEgEta);
EG->SetBranchAddress("l1tEgPhi",&l1tEgPhi);
EG->SetBranchAddress("l1tEgQual",&l1tEgQual);
EG->SetBranchAddress("l1tEgIso",&l1tEgIso);
EG->SetBranchAddress("l1tEgBx",&l1tEgBx);
EG->SetBranchAddress("egPt",&egPt);
EG->SetBranchAddress("egEta",&egEta);
EG->SetBranchAddress("egPhi",&egPhi);
EG->SetBranchAddress("IsUnprefirableEvent",&isUnprefirableEventEg);
EG->SetBranchAddress("L1t_bit",L1_bit_eg);//_bit_eg",L1_bit_eg);
EG->SetBranchAddress("L1FinalOR",&L1FinalOReg);

int entries_eg=EG->GetEntries();

//entries_eg=10000;

// EG
std::cout<<std::endl<<"Total EG objects: "<<entries_eg<<std::endl;
for (int i=0; i<entries_eg; i++)
{
	if(i%2000000==0)std::cout<<"Entry: "<<i<<" / "<<entries_eg<<std::endl;

	EG->GetEntry(i);

	if(abs(egEta)>2.5)continue;


	//only for l1 cut
	if( l1tEgPt>22. )
	{
		histo_eg_BX_l1Cut->Fill(l1tEgBx,1.);
		if(l1tEgBx==-2)histo_eg_pt_l1Cut[0]->Fill(egPt,1.);
		if(l1tEgBx==-1)
		{
			histo_eg_pt_l1Cut[1]->Fill(egPt,1.);
                        map_eta_phi_eg_l1Cut[0]->Fill(egEta,egPhi); //pre
		}
		if(l1tEgBx==0)histo_eg_pt_l1Cut[2]->Fill(egPt,1.);
		if(l1tEgBx==1)
		{
			histo_eg_pt_l1Cut[3]->Fill(egPt,1.);
                        map_eta_phi_eg_cut1[1]->Fill(egEta,egPhi); //post
		}
		if(l1tEgBx==2)histo_eg_pt_l1Cut[4]->Fill(egPt,1.);
		if(l1tEgBx==-2)histo_eg_eta_l1Cut[0]->Fill(egEta,1.);
                if(l1tEgBx==-1)histo_eg_eta_l1Cut[1]->Fill(egEta,1.);
                if(l1tEgBx==0)histo_eg_eta_l1Cut[2]->Fill(egEta,1.);  
                if(l1tEgBx==1)histo_eg_eta_l1Cut[3]->Fill(egEta,1.);  
                if(l1tEgBx==2)histo_eg_eta_l1Cut[4]->Fill(egEta,1.);
		
		// Unprefirable events
		if( isUnprefirableEventEg )
		{
			histo_eg_BX_l1Cut_unpref->Fill(l1tEgBx,1.);
	                if(l1tEgBx==-2)histo_eg_pt_l1Cut_unpref[0]->Fill(egPt,1.);
	                if(l1tEgBx==-1)
			{
				histo_eg_pt_l1Cut_unpref[1]->Fill(egPt,1.);
	                        map_eta_phi_eg_l1Cut_unpref[0]->Fill(egEta,egPhi); //pre
			}
	                if(l1tEgBx==0)histo_eg_pt_l1Cut_unpref[2]->Fill(egPt,1.);
	                if(l1tEgBx==1)
			{
				histo_eg_pt_l1Cut_unpref[3]->Fill(egPt,1.);
                        	map_eta_phi_eg_l1Cut_unpref[1]->Fill(egEta,egPhi); //post
			}
	                if(l1tEgBx==2)histo_eg_pt_l1Cut_unpref[4]->Fill(egPt,1.);
			if(l1tEgBx==-2)histo_eg_eta_l1Cut_unpref[0]->Fill(egEta,1.);
	                if(l1tEgBx==-1)histo_eg_eta_l1Cut_unpref[1]->Fill(egEta,1.);
                	if(l1tEgBx==0)histo_eg_eta_l1Cut_unpref[2]->Fill(egEta,1.);
        	        if(l1tEgBx==1)histo_eg_eta_l1Cut_unpref[3]->Fill(egEta,1.);
	                if(l1tEgBx==2)histo_eg_eta_l1Cut_unpref[4]->Fill(egEta,1.);
		}

	}
	//only for L1FinalOR
        if( L1FinalOReg )
        {
                histo_eg_BX_L1FinalOR->Fill(l1tEgBx,1.);
                if(l1tEgBx==-2)histo_eg_pt_L1FinalOR[0]->Fill(egPt,1.);  
                if(l1tEgBx==-1)
		{
			histo_eg_pt_L1FinalOR[1]->Fill(egPt,1.);
                        map_eta_phi_eg_L1FinalOR[0]->Fill(egEta,egPhi); //pre
		}
                if(l1tEgBx==0)histo_eg_pt_L1FinalOR[2]->Fill(egPt,1.);
                if(l1tEgBx==1)
		{
			histo_eg_pt_L1FinalOR[3]->Fill(egPt,1.);
                        map_eta_phi_eg_L1FinalOR[1]->Fill(egEta,egPhi); //post
		}
                if(l1tEgBx==2)histo_eg_pt_L1FinalOR[4]->Fill(egPt,1.);
		if(l1tEgBx==-2)histo_eg_eta_L1FinalOR[0]->Fill(egEta,1.);
                if(l1tEgBx==-1)histo_eg_eta_L1FinalOR[1]->Fill(egEta,1.);
                if(l1tEgBx==0)histo_eg_eta_L1FinalOR[2]->Fill(egEta,1.);
                if(l1tEgBx==1)histo_eg_eta_L1FinalOR[3]->Fill(egEta,1.);
                if(l1tEgBx==2)histo_eg_eta_L1FinalOR[4]->Fill(egEta,1.);

		// Unprefirable events
		if( isUnprefirableEventEg )
		{
			histo_eg_BX_L1FinalOR_unpref->Fill(l1tEgBx,1.);
	                if(l1tEgBx==-2)histo_eg_pt_L1FinalOR_unpref[0]->Fill(egPt,1.);
	                if(l1tEgBx==-1)
			{
				histo_eg_pt_L1FinalOR_unpref[1]->Fill(egPt,1.);
	                        map_eta_phi_eg_L1FinalOR_unpref[0]->Fill(egEta,egPhi); //pre
			}
	                if(l1tEgBx==0)histo_eg_pt_L1FinalOR_unpref[2]->Fill(egPt,1.);
	                if(l1tEgBx==1)
			{
				histo_eg_pt_L1FinalOR_unpref[3]->Fill(egPt,1.);
	                        map_eta_phi_eg_L1FinalOR_unpref[1]->Fill(egEta,egPhi); //post
			}
	                if(l1tEgBx==2)histo_eg_pt_L1FinalOR_unpref[4]->Fill(egPt,1.);
			if(l1tEgBx==-2)histo_eg_eta_L1FinalOR_unpref[0]->Fill(egEta,1.);
                        if(l1tEgBx==-1)histo_eg_eta_L1FinalOR_unpref[1]->Fill(egEta,1.);
                        if(l1tEgBx==0)histo_eg_eta_L1FinalOR_unpref[2]->Fill(egEta,1.);
                        if(l1tEgBx==1)histo_eg_eta_L1FinalOR_unpref[3]->Fill(egEta,1.);
                        if(l1tEgBx==2)histo_eg_eta_L1FinalOR_unpref[4]->Fill(egEta,1.);
		}
        }




	//rates vs eta
	if( egPt>12. && egPt<23. && l1tEgPt>15. && l1tEgPt<26.)
	{
		histo_eg_BX_cut1->Fill(l1tEgBx,1.);
		if(l1tEgBx==-2)histo_eg_eta_cut1[0]->Fill(egEta,1.);
		if(l1tEgBx==-1)
		{
			histo_eg_eta_cut1[1]->Fill(egEta,1.);
			map_eta_phi_eg_cut1[0]->Fill(egEta,egPhi); //pre
		}
		if(l1tEgBx==0)histo_eg_eta_cut1[2]->Fill(egEta,1.);
		if(l1tEgBx==1)
		{
			histo_eg_eta_cut1[3]->Fill(egEta,1.);
			map_eta_phi_eg_cut1[1]->Fill(egEta,egPhi); //post
		}
		if(l1tEgBx==2)histo_eg_eta_cut1[4]->Fill(egEta,1.);
	}
	
}

// pre
rate_vs_eta_eg_cut1_num[0]->Add(histo_eg_eta_cut1[1]);
rate_vs_eta_eg_cut1_den[0]->Add(histo_eg_eta_cut1[1]);
rate_vs_eta_eg_cut1_den[0]->Add(histo_eg_eta_cut1[2]);
rate_vs_eta_eg_cut1[0]->Divide(rate_vs_eta_eg_cut1_num[0],rate_vs_eta_eg_cut1_den[0]);

rate_vs_eta_eg_l1Cut_num[0]->Add(histo_eg_eta_l1Cut[1]);  
rate_vs_eta_eg_l1Cut_den[0]->Add(histo_eg_eta_l1Cut[1]);
rate_vs_eta_eg_l1Cut_den[0]->Add(histo_eg_eta_l1Cut[2]);
rate_vs_eta_eg_l1Cut[0]->Divide(rate_vs_eta_eg_l1Cut_num[0],rate_vs_eta_eg_l1Cut_den[0]);

rate_vs_eta_eg_l1Cut_unpref_num[0]->Add(histo_eg_eta_l1Cut_unpref[1]);  
rate_vs_eta_eg_l1Cut_unpref_den[0]->Add(histo_eg_eta_l1Cut_unpref[1]);
rate_vs_eta_eg_l1Cut_unpref_den[0]->Add(histo_eg_eta_l1Cut_unpref[2]);
rate_vs_eta_eg_l1Cut_unpref[0]->Divide(rate_vs_eta_eg_l1Cut_unpref_num[0],rate_vs_eta_eg_l1Cut_unpref_den[0]);

rate_vs_eta_eg_L1FinalOR_num[0]->Add(histo_eg_eta_L1FinalOR[1]);
rate_vs_eta_eg_L1FinalOR_den[0]->Add(histo_eg_eta_L1FinalOR[1]);
rate_vs_eta_eg_L1FinalOR_den[0]->Add(histo_eg_eta_L1FinalOR[2]);
rate_vs_eta_eg_L1FinalOR[0]->Divide(rate_vs_eta_eg_L1FinalOR_num[0],rate_vs_eta_eg_L1FinalOR_den[0]);

rate_vs_eta_eg_L1FinalOR_unpref_num[0]->Add(histo_eg_eta_L1FinalOR_unpref[1]);
rate_vs_eta_eg_L1FinalOR_unpref_den[0]->Add(histo_eg_eta_L1FinalOR_unpref[1]);
rate_vs_eta_eg_L1FinalOR_unpref_den[0]->Add(histo_eg_eta_L1FinalOR_unpref[2]);
rate_vs_eta_eg_L1FinalOR_unpref[0]->Divide(rate_vs_eta_eg_L1FinalOR_unpref_num[0],rate_vs_eta_eg_L1FinalOR_unpref_den[0]);

rate_vs_pt_eg_cut1_num[0]->Add(histo_eg_pt_cut1[1]);
rate_vs_pt_eg_cut1_den[0]->Add(histo_eg_pt_cut1[1]);
rate_vs_pt_eg_cut1_den[0]->Add(histo_eg_pt_cut1[2]);
rate_vs_pt_eg_cut1[0]->Divide(rate_vs_pt_eg_cut1_num[0], rate_vs_pt_eg_cut1_den[0]);

rate_vs_pt_eg_l1Cut_num[0]->Add(histo_eg_pt_l1Cut[1]);  
rate_vs_pt_eg_l1Cut_den[0]->Add(histo_eg_pt_l1Cut[1]);
rate_vs_pt_eg_l1Cut_den[0]->Add(histo_eg_pt_l1Cut[2]);
rate_vs_pt_eg_l1Cut[0]->Divide(rate_vs_pt_eg_l1Cut_num[0], rate_vs_pt_eg_l1Cut_den[0]);

rate_vs_pt_eg_l1Cut_unpref_num[0]->Add(histo_eg_pt_l1Cut_unpref[1]);  
rate_vs_pt_eg_l1Cut_unpref_den[0]->Add(histo_eg_pt_l1Cut_unpref[1]);
rate_vs_pt_eg_l1Cut_unpref_den[0]->Add(histo_eg_pt_l1Cut_unpref[2]);
rate_vs_pt_eg_l1Cut_unpref[0]->Divide(rate_vs_pt_eg_l1Cut_unpref_num[0], rate_vs_pt_eg_l1Cut_unpref_den[0]);

rate_vs_pt_eg_L1FinalOR_num[0]->Add(histo_eg_pt_L1FinalOR[1]);
rate_vs_pt_eg_L1FinalOR_den[0]->Add(histo_eg_pt_L1FinalOR[1]);
rate_vs_pt_eg_L1FinalOR_den[0]->Add(histo_eg_pt_L1FinalOR[2]);
rate_vs_pt_eg_L1FinalOR[0]->Divide(rate_vs_pt_eg_L1FinalOR_num[0], rate_vs_pt_eg_L1FinalOR_den[0]);

rate_vs_pt_eg_L1FinalOR_unpref_num[0]->Add(histo_eg_pt_L1FinalOR_unpref[1]);
rate_vs_pt_eg_L1FinalOR_unpref_den[0]->Add(histo_eg_pt_L1FinalOR_unpref[1]);
rate_vs_pt_eg_L1FinalOR_unpref_den[0]->Add(histo_eg_pt_L1FinalOR_unpref[2]);
rate_vs_pt_eg_L1FinalOR_unpref[0]->Divide(rate_vs_pt_eg_L1FinalOR_unpref_num[0], rate_vs_pt_eg_L1FinalOR_unpref_den[0]);


// post
rate_vs_eta_eg_cut1_num[1]->Add(histo_eg_eta_cut1[3]);
rate_vs_eta_eg_cut1_den[1]->Add(histo_eg_eta_cut1[3]);
rate_vs_eta_eg_cut1_den[1]->Add(histo_eg_eta_cut1[2]);
rate_vs_eta_eg_cut1[1]->Divide(rate_vs_eta_eg_cut1_num[1],rate_vs_eta_eg_cut1_den[1]);

rate_vs_eta_eg_l1Cut_num[1]->Add(histo_eg_eta_l1Cut[3]);
rate_vs_eta_eg_l1Cut_den[1]->Add(histo_eg_eta_l1Cut[3]);
rate_vs_eta_eg_l1Cut_den[1]->Add(histo_eg_eta_l1Cut[2]);
rate_vs_eta_eg_l1Cut[1]->Divide(rate_vs_eta_eg_l1Cut_num[1],rate_vs_eta_eg_l1Cut_den[1]);

rate_vs_eta_eg_l1Cut_unpref_num[1]->Add(histo_eg_eta_l1Cut_unpref[3]);
rate_vs_eta_eg_l1Cut_unpref_den[1]->Add(histo_eg_eta_l1Cut_unpref[3]);
rate_vs_eta_eg_l1Cut_unpref_den[1]->Add(histo_eg_eta_l1Cut_unpref[2]);
rate_vs_eta_eg_l1Cut_unpref[1]->Divide(rate_vs_eta_eg_l1Cut_unpref_num[1],rate_vs_eta_eg_l1Cut_unpref_den[1]);

rate_vs_eta_eg_L1FinalOR_num[1]->Add(histo_eg_eta_L1FinalOR[3]);
rate_vs_eta_eg_L1FinalOR_den[1]->Add(histo_eg_eta_L1FinalOR[3]);
rate_vs_eta_eg_L1FinalOR_den[1]->Add(histo_eg_eta_L1FinalOR[2]);
rate_vs_eta_eg_L1FinalOR[1]->Divide(rate_vs_eta_eg_L1FinalOR_num[1],rate_vs_eta_eg_L1FinalOR_den[1]);

rate_vs_eta_eg_L1FinalOR_unpref_num[1]->Add(histo_eg_eta_L1FinalOR_unpref[3]);
rate_vs_eta_eg_L1FinalOR_unpref_den[1]->Add(histo_eg_eta_L1FinalOR_unpref[3]);
rate_vs_eta_eg_L1FinalOR_unpref_den[1]->Add(histo_eg_eta_L1FinalOR_unpref[2]);
rate_vs_eta_eg_L1FinalOR_unpref[1]->Divide(rate_vs_eta_eg_L1FinalOR_unpref_num[1],rate_vs_eta_eg_L1FinalOR_unpref_den[1]);

rate_vs_pt_eg_cut1_num[1]->Add(histo_eg_pt_cut1[3]);
rate_vs_pt_eg_cut1_den[1]->Add(histo_eg_pt_cut1[3]);
rate_vs_pt_eg_cut1_den[1]->Add(histo_eg_pt_cut1[2]);
rate_vs_pt_eg_cut1[1]->Divide(rate_vs_pt_eg_cut1_num[1], rate_vs_pt_eg_cut1_den[1]);

rate_vs_pt_eg_l1Cut_num[1]->Add(histo_eg_pt_l1Cut[3]);
rate_vs_pt_eg_l1Cut_den[1]->Add(histo_eg_pt_l1Cut[3]);
rate_vs_pt_eg_l1Cut_den[1]->Add(histo_eg_pt_l1Cut[2]);
rate_vs_pt_eg_l1Cut[1]->Divide(rate_vs_pt_eg_l1Cut_num[1], rate_vs_pt_eg_l1Cut_den[1]);

rate_vs_pt_eg_l1Cut_unpref_num[1]->Add(histo_eg_pt_l1Cut_unpref[3]);
rate_vs_pt_eg_l1Cut_unpref_den[1]->Add(histo_eg_pt_l1Cut_unpref[3]);
rate_vs_pt_eg_l1Cut_unpref_den[1]->Add(histo_eg_pt_l1Cut_unpref[2]);
rate_vs_pt_eg_l1Cut_unpref[1]->Divide(rate_vs_pt_eg_l1Cut_unpref_num[1], rate_vs_pt_eg_l1Cut_unpref_den[1]);

rate_vs_pt_eg_L1FinalOR_num[1]->Add(histo_eg_pt_L1FinalOR[3]);
rate_vs_pt_eg_L1FinalOR_den[1]->Add(histo_eg_pt_L1FinalOR[3]);
rate_vs_pt_eg_L1FinalOR_den[1]->Add(histo_eg_pt_L1FinalOR[2]);
rate_vs_pt_eg_L1FinalOR[1]->Divide(rate_vs_pt_eg_L1FinalOR_num[1], rate_vs_pt_eg_L1FinalOR_den[1]);

rate_vs_pt_eg_L1FinalOR_unpref_num[1]->Add(histo_eg_pt_L1FinalOR_unpref[3]);
rate_vs_pt_eg_L1FinalOR_unpref_den[1]->Add(histo_eg_pt_L1FinalOR_unpref[3]);
rate_vs_pt_eg_L1FinalOR_unpref_den[1]->Add(histo_eg_pt_L1FinalOR_unpref[2]);
rate_vs_pt_eg_L1FinalOR_unpref[1]->Divide(rate_vs_pt_eg_L1FinalOR_unpref_num[1], rate_vs_pt_eg_L1FinalOR_unpref_den[1]);


// Total rates
cout <<endl<<endl<< "\033[1;33m===> For era: " << dataset <<"\033[0m";

std::cout<<std::endl<<"-----> Total rates <-----"<<std::endl;

float total_eg_pre_rate_cut1=(histo_eg_BX_cut1->GetBinContent(2))/(histo_eg_BX_cut1->GetBinContent(2)+histo_eg_BX_cut1->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for EG with L1/off cuts is "<<total_eg_pre_rate_cut1*100.<<"%"<<endl;
float total_eg_post_rate_cut1=(histo_eg_BX_cut1->GetBinContent(4))/(histo_eg_BX_cut1->GetBinContent(4)+histo_eg_BX_cut1->GetBinContent(3));
cout<<"The total post-firing rate for EG with L1/off cuts is "<<total_eg_post_rate_cut1*100.<<"%"<<endl<<endl;

float total_eg_pre_rate_l1Cut=(histo_eg_BX_l1Cut->GetBinContent(2))/(histo_eg_BX_l1Cut->GetBinContent(2)+histo_eg_BX_l1Cut->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for EG with L1EG>22 is "<<total_eg_pre_rate_l1Cut*100.<<"%"<<endl;
float total_eg_post_rate_l1Cut=(histo_eg_BX_l1Cut->GetBinContent(4))/(histo_eg_BX_l1Cut->GetBinContent(4)+histo_eg_BX_l1Cut->GetBinContent(3));
cout<<"The total post-firing rate for EG with L1EG>22 is "<<total_eg_post_rate_l1Cut*100.<<"%"<<endl;
float total_eg_pre_rate_l1Cut_unpref=(histo_eg_BX_l1Cut_unpref->GetBinContent(2))/(histo_eg_BX_l1Cut_unpref->GetBinContent(2)+histo_eg_BX_l1Cut_unpref->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for EG with L1EG>22 & unpref events is "<<total_eg_pre_rate_l1Cut_unpref*100.<<"%"<<endl;
float total_eg_post_rate_l1Cut_unpref=(histo_eg_BX_l1Cut_unpref->GetBinContent(4))/(histo_eg_BX_l1Cut_unpref->GetBinContent(4)+histo_eg_BX_l1Cut_unpref->GetBinContent(3));
cout<<"The total post-firing rate for EG with L1EG>22 & unpref events is "<<total_eg_post_rate_l1Cut_unpref*100.<<"%"<<endl<<endl;

float total_eg_pre_rate_L1FinalOR=(histo_eg_BX_L1FinalOR->GetBinContent(2))/(histo_eg_BX_L1FinalOR->GetBinContent(2)+histo_eg_BX_L1FinalOR->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for EG with L1FinalOR is "<<total_eg_pre_rate_L1FinalOR*100.<<"%"<<endl;
float total_eg_post_rate_L1FinalOR=(histo_eg_BX_L1FinalOR->GetBinContent(4))/(histo_eg_BX_L1FinalOR->GetBinContent(4)+histo_eg_BX_L1FinalOR->GetBinContent(3));
cout<<"The total post-firing rate for EG with L1FinalOR is "<<total_eg_post_rate_L1FinalOR*100.<<"%"<<endl;
float total_eg_pre_rate_L1FinalOR_unpref=(histo_eg_BX_L1FinalOR_unpref->GetBinContent(2))/(histo_eg_BX_L1FinalOR_unpref->GetBinContent(2)+histo_eg_BX_L1FinalOR_unpref->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for EG with L1FinalOR & unpref events is "<<total_eg_pre_rate_L1FinalOR_unpref*100.<<"%"<<endl;
float total_eg_post_rate_L1FinalOR_unpref=(histo_eg_BX_L1FinalOR_unpref->GetBinContent(4))/(histo_eg_BX_L1FinalOR_unpref->GetBinContent(4)+histo_eg_BX_L1FinalOR_unpref->GetBinContent(3));
cout<<"The total post-firing rate for EG with L1FinalOR & unpref events is "<<total_eg_post_rate_L1FinalOR_unpref*100.<<"%"<<endl<<endl;



TPaveText *paveCMS = new TPaveText(0.05,0.9,0.93,0.95,"NDC");
	paveCMS->AddText("#bf{CMS #it{Preliminary}}                  	     	    "+era_paveCMS+"            ("+energy_CoM+" TeV)");
	//paveCMS->AddText("#bf{CMS #it{Preliminary}}                RunF 2017 (13 TeV)");
	paveCMS->SetFillColor(0);
	paveCMS->SetBorderSize(0);
	paveCMS->SetTextSize(0.03);
	paveCMS->SetTextFont(42);

TPaveText *pave_eg_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_eg_cut1->AddText("L1EG");
	pave_eg_cut1->AddText("p_{T}^{e#gamma,L1} #in (15 , 26) GeV");//>15 & p_{T}^{e#gamma,L1}<26GeV");
	pave_eg_cut1->AddText("p_{T}^{e#gamma,offl} #in (12 , 23) GeV");//>12GeV & p_{T}^{e#gamma,offl}<23");
	pave_eg_cut1->AddText("|#eta_{e#gamma,offl}|<2.5");
	pave_eg_cut1->SetFillColor(0);
	pave_eg_cut1->SetBorderSize(0);
	pave_eg_cut1->SetTextSize(0.03);
	pave_eg_cut1->SetTextColor(kBlack);
	pave_eg_cut1->SetTextFont(42);

TPaveText *pave_eg_l1Cut = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
        pave_eg_l1Cut->AddText("L1EG");
	pave_eg_l1Cut->AddText("p_{T}^{e#gamma,L1} > 22 GeV");
	pave_eg_l1Cut->AddText("|#eta_{e#gamma,offl}|<2.5");
	pave_eg_l1Cut->SetFillColor(0);
	pave_eg_l1Cut->SetBorderSize(0);
	pave_eg_l1Cut->SetTextSize(0.03);
	pave_eg_l1Cut->SetTextColor(kBlack);
	pave_eg_l1Cut->SetTextFont(42);


TPaveText *pave_eg_l1Cut_unpref = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
        pave_eg_l1Cut_unpref->AddText("L1EG");
	pave_eg_l1Cut_unpref->AddText("Unprefirable events");
	pave_eg_l1Cut_unpref->AddText("p_{T}^{e#gamma,L1} > 22 GeV");
	pave_eg_l1Cut_unpref->AddText("|#eta_{e#gamma,offl}|<2.5");
	pave_eg_l1Cut_unpref->SetFillColor(0);
	pave_eg_l1Cut_unpref->SetBorderSize(0);
	pave_eg_l1Cut_unpref->SetTextSize(0.03);
	pave_eg_l1Cut_unpref->SetTextColor(kBlack);
	pave_eg_l1Cut_unpref->SetTextFont(42);
	
TPaveText *pave_eg_L1FinalOR = new TPaveText(0.6, 0.6, 0.85, 0.85, "NDC");
        pave_eg_L1FinalOR->AddText("L1EG");
	pave_eg_L1FinalOR->AddText("L1FinalOR");
	pave_eg_L1FinalOR->AddText("|#eta_{e#gamma,offl}|<2.5");
	pave_eg_L1FinalOR->SetFillColor(0);
	pave_eg_L1FinalOR->SetBorderSize(0);
	pave_eg_L1FinalOR->SetTextSize(0.03);
	pave_eg_L1FinalOR->SetTextColor(kBlack);
	pave_eg_L1FinalOR->SetTextFont(42);


TPaveText *pave_eg_L1FinalOR_unpref = new TPaveText(0.6, 0.6, 0.85, 0.85, "NDC");
        pave_eg_L1FinalOR_unpref->AddText("L1EG");
	pave_eg_L1FinalOR_unpref->AddText("Unprefirable events");
	pave_eg_L1FinalOR_unpref->AddText("L1FinalOR");
	pave_eg_L1FinalOR_unpref->AddText("|#eta_{e#gamma,offl}|<2.5");
	pave_eg_L1FinalOR_unpref->SetFillColor(0);
	pave_eg_L1FinalOR_unpref->SetBorderSize(0);
	pave_eg_L1FinalOR_unpref->SetTextSize(0.03);
	pave_eg_L1FinalOR_unpref->SetTextColor(kBlack);
	pave_eg_L1FinalOR_unpref->SetTextFont(42);



/// BX histos & rates

/// EGs
if(draw_eg)
{


//// BXs histos

TCanvas *c1=new TCanvas("c1","",800,600);
c1->cd();
c1->SetLogy();
histo_eg_BX_cut1->GetXaxis()->SetTitleOffset(1.2); 
histo_eg_BX_cut1->SetFillColor(0);
histo_eg_BX_cut1->SetLineWidth(2);
histo_eg_BX_cut1->SetLineColor(kBlue);
histo_eg_BX_cut1->SetMarkerSize(0.1);
histo_eg_BX_cut1->GetXaxis()->SetTitle("BX");
histo_eg_BX_cut1->GetYaxis()->SetTitle("Entries");
histo_eg_BX_cut1->Draw();
paveCMS->Draw("Same");
pave_eg_cut1->Draw("same");
if(save_canvas)c1->Print("../plots/"+dataset+"/eg_bx_cuts.png");

TCanvas *c01=new TCanvas("c01","",800,600);
c01->cd();
c01->SetLogy();
histo_eg_BX_l1Cut->GetXaxis()->SetTitleOffset(1.2); 
histo_eg_BX_l1Cut->SetFillColor(0);
histo_eg_BX_l1Cut->SetLineWidth(2);
histo_eg_BX_l1Cut->SetLineColor(kBlue);
histo_eg_BX_l1Cut->SetMarkerSize(0.1);
histo_eg_BX_l1Cut->GetXaxis()->SetTitle("BX");
histo_eg_BX_l1Cut->GetYaxis()->SetTitle("Entries");
histo_eg_BX_l1Cut->Draw();
paveCMS->Draw("Same");
pave_eg_l1Cut->Draw("same");
if(save_canvas)c01->Print("../plots/"+dataset+"/eg_bx_l1Cut.png");

TCanvas *c02=new TCanvas("c02","",800,600);
c02->cd();
c02->SetLogy();
histo_eg_BX_l1Cut_unpref->GetXaxis()->SetTitleOffset(1.2); 
histo_eg_BX_l1Cut_unpref->SetFillColor(0);
histo_eg_BX_l1Cut_unpref->SetLineWidth(2);
histo_eg_BX_l1Cut_unpref->SetLineColor(kBlue);
histo_eg_BX_l1Cut_unpref->SetMarkerSize(0.1);
histo_eg_BX_l1Cut_unpref->GetXaxis()->SetTitle("BX");
histo_eg_BX_l1Cut_unpref->GetYaxis()->SetTitle("Entries");
histo_eg_BX_l1Cut_unpref->Draw();
paveCMS->Draw("Same");
pave_eg_l1Cut_unpref->Draw("same");
if(save_canvas)c02->Print("../plots/"+dataset+"/eg_bx_l1Cut_unpref.png");


TCanvas *c001=new TCanvas("c001","",800,600);
c001->cd();
c001->SetLogy();
histo_eg_BX_L1FinalOR->GetXaxis()->SetTitleOffset(1.2); 
histo_eg_BX_L1FinalOR->SetFillColor(0);
histo_eg_BX_L1FinalOR->SetLineWidth(2);
histo_eg_BX_L1FinalOR->SetLineColor(kBlue);
histo_eg_BX_L1FinalOR->SetMarkerSize(0.1);
histo_eg_BX_L1FinalOR->GetXaxis()->SetTitle("BX");
histo_eg_BX_L1FinalOR->GetYaxis()->SetTitle("Entries");
histo_eg_BX_L1FinalOR->Draw();
paveCMS->Draw("Same");
pave_eg_L1FinalOR->Draw("same");
if(save_canvas)c001->Print("../plots/"+dataset+"/eg_bx_L1FinalOR.png");

TCanvas *c002=new TCanvas("c002","",800,600);
c002->cd();
c002->SetLogy();
histo_eg_BX_L1FinalOR_unpref->GetXaxis()->SetTitleOffset(1.2); 
histo_eg_BX_L1FinalOR_unpref->SetFillColor(0);
histo_eg_BX_L1FinalOR_unpref->SetLineWidth(2);
histo_eg_BX_L1FinalOR_unpref->SetLineColor(kBlue);
histo_eg_BX_L1FinalOR_unpref->SetMarkerSize(0.1);
histo_eg_BX_L1FinalOR_unpref->GetXaxis()->SetTitle("BX");
histo_eg_BX_L1FinalOR_unpref->GetYaxis()->SetTitle("Entries");
histo_eg_BX_L1FinalOR_unpref->Draw();
paveCMS->Draw("Same");
pave_eg_L1FinalOR_unpref->Draw("same");
if(save_canvas)c002->Print("../plots/"+dataset+"/eg_bx_L1FinalOR_unpref.png");




/// Rates vs eta histos 

TLegend *leg_cut1=new TLegend(.2,.7,.45,.85);
leg_cut1->AddEntry(rate_vs_eta_eg_cut1[0],"Pre-firing","lp");
leg_cut1->AddEntry(rate_vs_eta_eg_cut1[1],"Post-firing","lp");
leg_cut1->SetTextSize(0.02);
TCanvas *c2=new TCanvas("c2","",800,600);
c2->cd();
rate_vs_eta_eg_cut1[0]->SetFillColor(0);
rate_vs_eta_eg_cut1[0]->SetLineWidth(2);
rate_vs_eta_eg_cut1[0]->SetLineColor(kBlue);
rate_vs_eta_eg_cut1[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_eta_eg_cut1[0]->SetMarkerSize(0.1);
rate_vs_eta_eg_cut1[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_eg_cut1[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_eta_eg_cut1[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_eg_cut1[0]->Draw("ep");
rate_vs_eta_eg_cut1[1]->SetLineWidth(2);
rate_vs_eta_eg_cut1[1]->SetLineColor(kRed);
rate_vs_eta_eg_cut1[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_cut1->Draw("same");
leg_cut1->Draw("SAME");
if(save_canvas)c2->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_eta_cut1.png");

TLegend *leg_l1Cut=new TLegend(.2,.7,.45,.85);
leg_l1Cut->AddEntry(rate_vs_eta_eg_cut1[0],"Pre-firing","lp");
leg_l1Cut->AddEntry(rate_vs_eta_eg_cut1[1],"Post-firing","lp");
leg_l1Cut->SetTextSize(0.02);
TCanvas *c3=new TCanvas("c3","",800,600);
c3->cd();
rate_vs_eta_eg_l1Cut[0]->SetFillColor(0);
rate_vs_eta_eg_l1Cut[0]->SetLineWidth(2);
rate_vs_eta_eg_l1Cut[0]->SetLineColor(kBlue);
rate_vs_eta_eg_l1Cut[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_eta_eg_l1Cut[0]->SetMarkerSize(0.1);
rate_vs_eta_eg_l1Cut[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_eg_l1Cut[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_eta_eg_l1Cut[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_eg_l1Cut[0]->Draw("ep");
rate_vs_eta_eg_l1Cut[1]->SetLineWidth(2);
rate_vs_eta_eg_l1Cut[1]->SetLineColor(kRed);
rate_vs_eta_eg_l1Cut[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_l1Cut->Draw("same");
leg_l1Cut->Draw("SAME");
if(save_canvas)c3->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_eta_l1Cut.png");

TLegend *leg_l1Cut_unpref=new TLegend(.2,.7,.45,.85);
leg_l1Cut_unpref->AddEntry(rate_vs_eta_eg_cut1[0],"Pre-firing","lp");
leg_l1Cut_unpref->AddEntry(rate_vs_eta_eg_cut1[1],"Post-firing","lp");
leg_l1Cut_unpref->SetTextSize(0.02);
TCanvas *c4=new TCanvas("c4","",800,600);
c4->cd();
rate_vs_eta_eg_l1Cut_unpref[0]->SetFillColor(0);
rate_vs_eta_eg_l1Cut_unpref[0]->SetLineWidth(2);
rate_vs_eta_eg_l1Cut_unpref[0]->SetLineColor(kBlue);
rate_vs_eta_eg_l1Cut_unpref[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_eta_eg_l1Cut_unpref[0]->SetMarkerSize(0.1);
rate_vs_eta_eg_l1Cut_unpref[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_eg_l1Cut_unpref[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_eta_eg_l1Cut_unpref[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_eg_l1Cut_unpref[0]->Draw("ep");
rate_vs_eta_eg_l1Cut_unpref[1]->SetLineWidth(2);
rate_vs_eta_eg_l1Cut_unpref[1]->SetLineColor(kRed);
rate_vs_eta_eg_l1Cut_unpref[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_l1Cut_unpref->Draw("same");
leg_l1Cut_unpref->Draw("SAME");
if(save_canvas)c4->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_eta_l1Cut_unpref.png");

TLegend *leg_L1FinalOR=new TLegend(.2,.7,.45,.85);
leg_L1FinalOR->AddEntry(rate_vs_eta_eg_cut1[0],"Pre-firing","lp");
leg_L1FinalOR->AddEntry(rate_vs_eta_eg_cut1[1],"Post-firing","lp");
leg_L1FinalOR->SetTextSize(0.02);
TCanvas *c5=new TCanvas("c5","",800,600);
c5->cd();
rate_vs_eta_eg_L1FinalOR[0]->SetFillColor(0);
rate_vs_eta_eg_L1FinalOR[0]->SetLineWidth(2);
rate_vs_eta_eg_L1FinalOR[0]->SetLineColor(kBlue);
rate_vs_eta_eg_L1FinalOR[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_eta_eg_L1FinalOR[0]->SetMarkerSize(0.1);
rate_vs_eta_eg_L1FinalOR[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_eg_L1FinalOR[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_eta_eg_L1FinalOR[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_eg_L1FinalOR[0]->Draw("ep");
rate_vs_eta_eg_L1FinalOR[1]->SetLineWidth(2);
rate_vs_eta_eg_L1FinalOR[1]->SetLineColor(kRed);
rate_vs_eta_eg_L1FinalOR[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_L1FinalOR->Draw("same");
leg_L1FinalOR->Draw("SAME");
if(save_canvas)c5->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_eta_L1FinalOR.png");

TLegend *leg_L1FinalOR_unpref=new TLegend(.2,.7,.45,.85);
leg_L1FinalOR_unpref->AddEntry(rate_vs_eta_eg_cut1[0],"Pre-firing","lp");
leg_L1FinalOR_unpref->AddEntry(rate_vs_eta_eg_cut1[1],"Post-firing","lp");
leg_L1FinalOR_unpref->SetTextSize(0.02);
TCanvas *c6=new TCanvas("c6","",800,600);
c6->cd();
rate_vs_eta_eg_L1FinalOR_unpref[0]->SetFillColor(0);
rate_vs_eta_eg_L1FinalOR_unpref[0]->SetLineWidth(2);
rate_vs_eta_eg_L1FinalOR_unpref[0]->SetLineColor(kBlue);
rate_vs_eta_eg_L1FinalOR_unpref[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_eta_eg_L1FinalOR_unpref[0]->SetMarkerSize(0.1);
rate_vs_eta_eg_L1FinalOR_unpref[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_eg_L1FinalOR_unpref[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_eta_eg_L1FinalOR_unpref[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_eg_L1FinalOR_unpref[0]->Draw("ep");
rate_vs_eta_eg_L1FinalOR_unpref[1]->SetLineWidth(2);
rate_vs_eta_eg_L1FinalOR_unpref[1]->SetLineColor(kRed);
rate_vs_eta_eg_L1FinalOR_unpref[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_L1FinalOR_unpref->Draw("same");
leg_L1FinalOR_unpref->Draw("SAME");
if(save_canvas)c6->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_eta_L1FinalOR_unpref.png");



/// Rates vs eta histos 

TLegend *leg_l1Cut_pt=new TLegend(.2,.7,.45,.85);
leg_l1Cut_pt->AddEntry(rate_vs_pt_eg_l1Cut[0],"Pre-firing","lp");
leg_l1Cut_pt->AddEntry(rate_vs_pt_eg_l1Cut[1],"Post-firing","lp");
leg_l1Cut_pt->SetTextSize(0.02);
TCanvas *c7=new TCanvas("c7","",800,600);
c7->cd();
rate_vs_pt_eg_l1Cut[0]->SetFillColor(0);
rate_vs_pt_eg_l1Cut[0]->SetLineWidth(2);
rate_vs_pt_eg_l1Cut[0]->SetLineColor(kBlue);
rate_vs_pt_eg_l1Cut[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_pt_eg_l1Cut[0]->SetMarkerSize(0.1);
rate_vs_pt_eg_l1Cut[0]->GetXaxis()->SetTitle("#p_{T}^{offl}");
rate_vs_pt_eg_l1Cut[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_pt_eg_l1Cut[0]->GetYaxis()->SetTitle("Rate");
rate_vs_pt_eg_l1Cut[0]->Draw("ep");
rate_vs_pt_eg_l1Cut[1]->SetLineWidth(2);
rate_vs_pt_eg_l1Cut[1]->SetLineColor(kRed);
rate_vs_pt_eg_l1Cut[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_l1Cut->Draw("same");
leg_l1Cut_pt->Draw("SAME");
if(save_canvas) c7->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_pt_l1Cut.png");

TLegend *leg_l1Cut_unpref_pt=new TLegend(.2,.7,.45,.85);
leg_l1Cut_unpref_pt->AddEntry(rate_vs_pt_eg_l1Cut_unpref[0],"Pre-firing","lp");
leg_l1Cut_unpref_pt->AddEntry(rate_vs_pt_eg_l1Cut_unpref[1],"Post-firing","lp");
leg_l1Cut_unpref_pt->SetTextSize(0.02);
TCanvas *c8=new TCanvas("c8","",800,600);
c8->cd();
rate_vs_pt_eg_l1Cut_unpref[0]->SetFillColor(0);
rate_vs_pt_eg_l1Cut_unpref[0]->SetLineWidth(2);
rate_vs_pt_eg_l1Cut_unpref[0]->SetLineColor(kBlue);
rate_vs_pt_eg_l1Cut_unpref[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_pt_eg_l1Cut_unpref[0]->SetMarkerSize(0.1);
rate_vs_pt_eg_l1Cut_unpref[0]->GetXaxis()->SetTitle("#p_{T}^{offl}");
rate_vs_pt_eg_l1Cut_unpref[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_pt_eg_l1Cut_unpref[0]->GetYaxis()->SetTitle("Rate");
rate_vs_pt_eg_l1Cut_unpref[0]->Draw("ep");
rate_vs_pt_eg_l1Cut_unpref[1]->SetLineWidth(2);
rate_vs_pt_eg_l1Cut_unpref[1]->SetLineColor(kRed);
rate_vs_pt_eg_l1Cut_unpref[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_l1Cut_unpref->Draw("same");
leg_l1Cut_unpref_pt->Draw("SAME");
if(save_canvas) c8->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_pt_l1Cut_unpref.png");

TLegend *leg_L1FinalOR_pt=new TLegend(.2,.7,.45,.85);
leg_L1FinalOR_pt->AddEntry(rate_vs_pt_eg_L1FinalOR[0],"Pre-firing","lp");
leg_L1FinalOR_pt->AddEntry(rate_vs_pt_eg_L1FinalOR[1],"Post-firing","lp");
leg_L1FinalOR_pt->SetTextSize(0.02);
TCanvas *c9=new TCanvas("c9","",800,600);
c9->cd();
rate_vs_pt_eg_L1FinalOR[0]->SetFillColor(0);
rate_vs_pt_eg_L1FinalOR[0]->SetLineWidth(2);
rate_vs_pt_eg_L1FinalOR[0]->SetLineColor(kBlue);
rate_vs_pt_eg_L1FinalOR[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_pt_eg_L1FinalOR[0]->SetMarkerSize(0.1);
rate_vs_pt_eg_L1FinalOR[0]->GetXaxis()->SetTitle("#p_{T}^{offl}");
rate_vs_pt_eg_L1FinalOR[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_pt_eg_L1FinalOR[0]->GetYaxis()->SetTitle("Rate");
rate_vs_pt_eg_L1FinalOR[0]->Draw("ep");
rate_vs_pt_eg_L1FinalOR[1]->SetLineWidth(2);
rate_vs_pt_eg_L1FinalOR[1]->SetLineColor(kRed);
rate_vs_pt_eg_L1FinalOR[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_L1FinalOR->Draw("same");
leg_L1FinalOR_pt->Draw("SAME");
if(save_canvas) c9->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_pt_L1FinalOR.png");

TLegend *leg_L1FinalOR_unpref_pt=new TLegend(.2,.7,.45,.85);
leg_L1FinalOR_unpref_pt->AddEntry(rate_vs_pt_eg_L1FinalOR_unpref[0],"Pre-firing","lp");
leg_L1FinalOR_unpref_pt->AddEntry(rate_vs_pt_eg_L1FinalOR_unpref[1],"Post-firing","lp");
leg_L1FinalOR_unpref_pt->SetTextSize(0.02);
TCanvas *c10=new TCanvas("c10","",800,600);
c10->cd();
rate_vs_pt_eg_L1FinalOR_unpref[0]->SetFillColor(0);
rate_vs_pt_eg_L1FinalOR_unpref[0]->SetLineWidth(2);
rate_vs_pt_eg_L1FinalOR_unpref[0]->SetLineColor(kBlue);
rate_vs_pt_eg_L1FinalOR_unpref[0]->GetYaxis()->SetRangeUser(0.,.051);
rate_vs_pt_eg_L1FinalOR_unpref[0]->SetMarkerSize(0.1);
rate_vs_pt_eg_L1FinalOR_unpref[0]->GetXaxis()->SetTitle("#p_{T}^{offl}");
rate_vs_pt_eg_L1FinalOR_unpref[0]->GetYaxis()->SetTitleOffset(1.2);
rate_vs_pt_eg_L1FinalOR_unpref[0]->GetYaxis()->SetTitle("Rate");
rate_vs_pt_eg_L1FinalOR_unpref[0]->Draw("ep");
rate_vs_pt_eg_L1FinalOR_unpref[1]->SetLineWidth(2);
rate_vs_pt_eg_L1FinalOR_unpref[1]->SetLineColor(kRed);
rate_vs_pt_eg_L1FinalOR_unpref[1]->Draw("SAME");
paveCMS->Draw("Same");
pave_eg_L1FinalOR_unpref->Draw("same");
leg_L1FinalOR_unpref_pt->Draw("SAME");
if(save_canvas) c10->Print("../plots/"+dataset+"/others/eg_pre_rate_vs_pt_L1FinalOR_unpref.png");


}


if(create_histos_root_file)
{
	TFile *f=new TFile("../plots/"+dataset+"/"+outFile,"RECREATE");
	f->cd();
	histo_eg_BX_cut1->SetName("eg_BX_cut1");
	histo_eg_BX_cut1->Write();
	rate_vs_eta_eg_cut1[0]->SetName("eg_rate_vs_eta_pre_cut1");
	rate_vs_eta_eg_cut1[0]->Write();
	rate_vs_eta_eg_cut1[1]->SetName("eg_rate_vs_eta_post_cut1");
	rate_vs_eta_eg_cut1[1]->Write();
	
	histo_eg_BX_l1Cut->SetName("eg_BX_l1Cut");
	histo_eg_BX_l1Cut->Write();
	rate_vs_eta_eg_l1Cut[0]->SetName("eg_rate_vs_eta_pre_l1Cut");
	rate_vs_eta_eg_l1Cut[0]->Write();
	rate_vs_eta_eg_l1Cut[1]->SetName("eg_rate_vs_eta_post_l1Cut");
	rate_vs_eta_eg_l1Cut[1]->Write();
	rate_vs_pt_eg_l1Cut[0]->SetName("eg_rate_vs_pt_pre_l1Cut");
	rate_vs_pt_eg_l1Cut[0]->Write();
	rate_vs_pt_eg_l1Cut[1]->SetName("eg_rate_vs_pt_post_l1Cut");
	rate_vs_pt_eg_l1Cut[1]->Write();
	
	histo_eg_BX_l1Cut_unpref->SetName("eg_BX_l1Cut_unpref");
	histo_eg_BX_l1Cut_unpref->Write();
	rate_vs_eta_eg_l1Cut_unpref[0]->SetName("eg_rate_vs_eta_pre_l1Cut_unpref");
	rate_vs_eta_eg_l1Cut_unpref[0]->Write();
	rate_vs_eta_eg_l1Cut_unpref[1]->SetName("eg_rate_vs_eta_post_l1Cut_unpref");
	rate_vs_eta_eg_l1Cut_unpref[1]->Write();
	rate_vs_pt_eg_l1Cut_unpref[0]->SetName("eg_rate_vs_pt_pre_l1Cut_unpref");
	rate_vs_pt_eg_l1Cut_unpref[0]->Write();
	rate_vs_pt_eg_l1Cut_unpref[1]->SetName("eg_rate_vs_pt_post_l1Cut_unpref");
	rate_vs_pt_eg_l1Cut_unpref[1]->Write();

	histo_eg_BX_L1FinalOR->SetName("eg_BX_L1FinalOR");
	histo_eg_BX_L1FinalOR->Write();
	rate_vs_eta_eg_L1FinalOR[0]->SetName("eg_rate_vs_eta_pre_L1FinalOR");
	rate_vs_eta_eg_L1FinalOR[0]->Write();
	rate_vs_eta_eg_L1FinalOR[1]->SetName("eg_rate_vs_eta_post_L1FinalOR");
	rate_vs_eta_eg_L1FinalOR[1]->Write();
	rate_vs_pt_eg_L1FinalOR[0]->SetName("eg_rate_vs_pt_pre_L1FinalOR");
	rate_vs_pt_eg_L1FinalOR[0]->Write();
	rate_vs_pt_eg_L1FinalOR[1]->SetName("eg_rate_vs_pt_post_L1FinalOR");
	rate_vs_pt_eg_L1FinalOR[1]->Write();

	histo_eg_BX_L1FinalOR_unpref->SetName("eg_BX_L1FinalOR_unpref");
	histo_eg_BX_L1FinalOR_unpref->Write();
	rate_vs_eta_eg_L1FinalOR_unpref[0]->SetName("eg_rate_vs_eta_pre_L1FinalOR_unpref");
	rate_vs_eta_eg_L1FinalOR_unpref[0]->Write();
	rate_vs_eta_eg_L1FinalOR_unpref[1]->SetName("eg_rate_vs_eta_post_L1FinalOR_unpref");
	rate_vs_eta_eg_L1FinalOR_unpref[1]->Write();
	rate_vs_pt_eg_L1FinalOR_unpref[0]->SetName("eg_rate_vs_pt_pre_L1FinalOR_unpref");
	rate_vs_pt_eg_L1FinalOR_unpref[0]->Write();
	rate_vs_pt_eg_L1FinalOR_unpref[1]->SetName("eg_rate_vs_pt_post_L1FinalOR_unpref");
	rate_vs_pt_eg_L1FinalOR_unpref[1]->Write();



	f->Close();
}



}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///////////////  end of code ///////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/*
-> objects cuts !
-----------------------------------
cut1_EGs:	l1tPt in (15,26)
		offPt in (12,23)
-----------------------------------
		
-> Names of histos:
histo_eg_eta_cut1->
histo_mu_eta_cut1->
histo_mu_eta_cut2->
histo_jet_eta_cut1->
rate_vs_eta_eg_cut1->
rate_vs_eta_eg_cut1_num->
rate_vs_eta_eg_cut1_den->
rate_vs_eta_mu_cut1->
rate_vs_eta_mu_cut1_num->
rate_vs_eta_mu_cut1_den->
rate_vs_eta_mu_cut2->
rate_vs_eta_mu_cut2_num->
rate_vs_eta_mu_cut2_den->
rate_vs_eta_jet_cut1->
rate_vs_eta_jet_cut1_num->
rate_vs_eta_jet_cut1_den->

*/
