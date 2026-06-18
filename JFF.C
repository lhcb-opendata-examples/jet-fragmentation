#include "ROOT/RDataFrame.hxx"
#include "ROOT/RDF/Utils.hxx" 
#include <ROOT/RDFHelpers.hxx>
#include "ROOT/RVec.hxx"
#include "TH1D.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TCanvas.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include "TLegend.h"

auto apply_id_mask(int target_id) {
    // Capture target_id by value so the lambda remembers it
    return [target_id](const ROOT::VecOps::RVec<float>& var_values, 
                       const ROOT::VecOps::RVec<float>& ids) {
        return var_values[ROOT::VecOps::abs(ids) == target_id];
    };
}

void JFF()
{
    // Enable xrootd logging (this acutally helps to significantly speed up the multithreaded processing)
    gSystem->Setenv("XRD_LOGLEVEL", "Debug");

    // Redirect the resulting text away from the terminal screen
    gSystem->Setenv("XRD_LOGFILE", "output/xrootd_debug_stream.log");
    // Enable implicit multi-threading for fast, asynchronous background reading over XRootD
    ROOT::EnableImplicitMT();

    // Force ROOT to stream data packets ahead of time on a background thread
    gEnv->SetValue("TFile.AsyncPrefetching", 1);

    // Expand the network cache size from 30MB to 200MB
    gEnv->SetValue("TTreeCache.Size", 200000000); 
    std::vector<std::string> fileList = {
        /*
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00392998_00000001_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00392998_00000002_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00392999_00000001_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393002_00000001_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393002_00000002_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393002_00000003_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393002_00000004_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393002_00000005_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393003_00000001_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393003_00000002_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393003_00000003_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393003_00000004_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393003_00000005_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393006_00000001_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393006_00000002_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393006_00000003_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393006_00000004_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393006_00000005_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393007_00000001_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393007_00000002_1.dvntuple.root",
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393007_00000003_1.dvntuple.root",
        */
        "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00393007_00000004_1.dvntuple.root"
    };

    // Set up custom bins
    std::vector<double> ptbins = {20., 30., 50., 100.};
    int nptbins = ptbins.size() - 1;

    const int nbins = 20;
    double zmin = 1e-3;   double zmax = 1.0;
    double jtmin = 1e-3;  double jtmax = 10;

    double bins[nbins + 1];
    double jtbins[nbins + 1];

    double logmin = std::log10(zmin);   double logmax = std::log10(zmax);
    double logjtmin = std::log10(jtmin); double logjtmax = std::log10(jtmax);

    for (int i = 0; i <= nbins; i++) {
        bins[i] = std::pow(10, logmin + (logmax - logmin) * i / nbins);
        jtbins[i] = std::pow(10, logjtmin + (logjtmax - logjtmin) * i / nbins);
    }

    // Initialize RDataFrame
    ROOT::RDataFrame df("dijets/DecayTree", fileList);

    #if ROOT_VERSION_CODE >= ROOT_VERSION(6,26,0)
    ROOT::RDF::Experimental::AddProgressBar(df);
    #else
    std::cout << "Processing started... (Progress bar disabled: requires ROOT v6.26+)" << std::endl;
    #endif
    //ROOT::RDF::Experimental::AddProgressBar(df); 

    // CALCULATE CONSTITUENT OBSERVABLES (z, jt, r) USING VECTORIZED LAMBDAS
    // We pass the jet values and the constituent RVecs. We return a new RVec of calculated values per event.

    // Calculate z array
    auto pipeline = df.Define("z_vec", [](double jpx, double jpy, double jpz, 
                                         const ROOT::RVec<Float_t>& cpx, const ROOT::RVec<Float_t>& cpy, const ROOT::RVec<Float_t>& cpz, const ROOT::RVec<Float_t>& cpid, const ROOT::RVec<Float_t>& cq) {
        TVector3 jet3vec(jpx / 1000., jpy / 1000., jpz / 1000.);
        double jet3vec_mag2 = jet3vec.Mag2();
        
        ROOT::RVec<double> z_values;
        z_values.reserve(cpx.size());
        for (size_t i = 0; i < cpx.size(); ++i) {
            if (cq[i] == 0 || fabs(cpid[i]) <= 100) {
                continue;
            }
            TVector3 con3vec(cpx[i] / 1000., cpy[i] / 1000., cpz[i] / 1000.);
            double z_val = (con3vec * jet3vec) / jet3vec_mag2;
            z_values.push_back(z_val);
        }
        return z_values;
    }, {"CELLjet_0_PX", "CELLjet_0_PY", "CELLjet_0_PZ", "CELLjet_0_Constituents_pX", "CELLjet_0_Constituents_pY", "CELLjet_0_Constituents_pZ", "CELLjet_0_Constituents_ID", "CELLjet_0_Constituents_Q"})

    // Calculate jt array
    .Define("jt_vec", [](double jpx, double jpy, double jpz, 
                                            const ROOT::RVec<Float_t>& cpx, const ROOT::RVec<Float_t>& cpy, const ROOT::RVec<Float_t>& cpz, const ROOT::RVec<Float_t>& cpid, const ROOT::RVec<Float_t>& cq) {
        TVector3 jet3vec(jpx / 1000., jpy / 1000., jpz / 1000.);
        double jet3vec_mag = jet3vec.Mag();
        
        ROOT::RVec<double> jt_values;
        jt_values.reserve(cpx.size());
        for (size_t i = 0; i < cpx.size(); ++i) {
            if (cq[i] == 0 || fabs(cpid[i]) <= 100) {
                continue;
            }
            TVector3 con3vec(cpx[i] / 1000., cpy[i] / 1000., cpz[i] / 1000.);
            double jt_val = (con3vec.Cross(jet3vec)).Mag() / jet3vec_mag;
            jt_values.push_back(jt_val);
        }
        return jt_values;
    }, {"CELLjet_0_PX", "CELLjet_0_PY", "CELLjet_0_PZ", "CELLjet_0_Constituents_pX", "CELLjet_0_Constituents_pY", "CELLjet_0_Constituents_pZ", "CELLjet_0_Constituents_ID", "CELLjet_0_Constituents_Q"})

    // Calculate DeltaR (r) array
    .Define("r_vec", [](double jpx, double jpy, double jpz, double je,
                                           const ROOT::RVec<Float_t>& cpx, const ROOT::RVec<Float_t>& cpy, const ROOT::RVec<Float_t>& cpz, const ROOT::RVec<Float_t>& ce, const ROOT::RVec<Float_t>& cpid, const ROOT::RVec<Float_t>& cq) {
        TLorentzVector jet(jpx / 1000., jpy / 1000., jpz / 1000., je / 1000.);
        
        ROOT::RVec<double> r_values;
        r_values.reserve(cpx.size());
        for (size_t i = 0; i < cpx.size(); ++i) {
            if (cq[i] == 0 || fabs(cpid[i]) <= 100) {
                continue;
            }
            TLorentzVector con(cpx[i] / 1000., cpy[i] / 1000., cpz[i] / 1000., ce[i] / 1000.);
            double r_val = con.DeltaR(jet);
            r_values.push_back(r_val);
        }
        return r_values;
    }, {"CELLjet_0_PX", "CELLjet_0_PY", "CELLjet_0_PZ", "CELLjet_0_PE", "CELLjet_0_Constituents_pX", "CELLjet_0_Constituents_pY", "CELLjet_0_Constituents_pZ", "CELLjet_0_Constituents_E", "CELLjet_0_Constituents_ID", "CELLjet_0_Constituents_Q"})

    // Define a column with jet pT in GeV
    .Define("jet_pt_GeV", "CELLjet_0_PT / 1000.0")

    // Filter PID probabilities for assigned PID hypothesis
    .Define("proton_NNp", apply_id_mask(2212), {"CELLjet_0_Constituents_NNp",  "CELLjet_0_Constituents_ID"})
    .Define("kaon_NNk", apply_id_mask(321), {"CELLjet_0_Constituents_NNk",  "CELLjet_0_Constituents_ID"})
    .Define("pion_NNpi", apply_id_mask(211), {"CELLjet_0_Constituents_NNpi",  "CELLjet_0_Constituents_ID"});

    auto ptLow = pipeline.Filter([](double pt) { 
        return pt >= 20000.0 && pt < 30000.0; 
    }, {"CELLjet_0_PT"});    

    auto ptMed = pipeline.Filter([](double pt) { 
        return pt >= 30000.0 && pt < 50000.0; 
    }, {"CELLjet_0_PT"});

    auto ptHigh = pipeline.Filter([](double pt) { 
        return pt >= 50000.0 && pt < 100000.0; 
    }, {"CELLjet_0_PT"});

    // BOOK HISTOGRAMS
    gStyle->SetOptStat(0);

    auto hpt_norm = pipeline.Histo1D({"hpt_norm", ";p_{T,jet} [GeV/c];", nptbins, ptbins.data()}, "jet_pt_GeV");

    auto hz  = pipeline.Histo1D({"hz", ";#it{z};#frac{d#it{N}}{d#it{z}}", nbins, bins}, "z_vec");
    auto hjt = pipeline.Histo1D({"hjt", ";#it{j_{T}} [GeV/c];#frac{d#it{N}}{d#it{j_{T}}}", nbins, jtbins}, "jt_vec");
    auto hr  = pipeline.Histo1D({"hr", ";#it{#DeltaR}(h,jet);#frac{d#it{N}}{d#it{r}}", 40, 0., 0.5}, "r_vec");

    auto hp_NNp = pipeline.Histo1D({"p_NNp", ";prob_NNp;", 40, 0., 1.0}, "proton_NNp");
    auto hk_NNk = pipeline.Histo1D({"k_NNk", ";prob_NNk;", 40, 0., 1.0}, "kaon_NNk");
    auto hpi_NNpi = pipeline.Histo1D({"pi_NNpi", ";prob_NNk;", 40, 0., 1.0}, "pion_NNpi");

    auto hz_ptlow  = ptLow.Histo1D({"hz_ptlow", ";#it{z};#frac{d#it{N}}{d#it{z}}", nbins, bins}, "z_vec");
    auto hz_ptmed  = ptMed.Histo1D({"hz_ptmed", ";#it{z};#frac{d#it{N}}{d#it{z}}", nbins, bins}, "z_vec");
    auto hz_pthigh  = ptHigh.Histo1D({"hz_pthigh", ";#it{z};#frac{d#it{N}}{d#it{z}}", nbins, bins}, "z_vec");

    auto hjt_ptlow = ptLow.Histo1D({"hjt_ptlow", ";#it{j_{T}} [GeV/c];#frac{d#it{N}}{d#it{j_{T}}}", nbins, jtbins}, "jt_vec");
    auto hjt_ptmed = ptMed.Histo1D({"hjt_ptmed", ";#it{j_{T}} [GeV/c];#frac{d#it{N}}{d#it{j_{T}}}", nbins, jtbins}, "jt_vec");
    auto hjt_pthigh = ptHigh.Histo1D({"hjt_pthigh", ";#it{j_{T}} [GeV/c];#frac{d#it{N}}{d#it{j_{T}}}", nbins, jtbins}, "jt_vec");

    auto hr_ptlow  = ptLow.Histo1D({"hr_ptlow", ";#it{#DeltaR}(h, jet);#frac{d#it{N}}{d#it{r}};", 40, 0., 0.5}, "r_vec");
    auto hr_ptmed  = ptMed.Histo1D({"hr_ptmed", ";#it{DeltaR})(h, jet);#frac{d#it{N}}{d#it{r}}", 40, 0., 0.5}, "r_vec");
    auto hr_pthigh  = ptHigh.Histo1D({"hr_pthigh", ";#it{#DeltaR}(h, jet);#frac{d#it{N}}{d#it{r}}", 40, 0., 0.5}, "r_vec");



    // TRIGGER THE EVENT LOOP
    std::cout << "Streaming data and processing multi-threaded..." << std::endl;

    TFile *outfile = new TFile("output/JFF_hists.root", "RECREATE");
    outfile->cd();

    hpt_norm->Write();

    hp_NNp->Write();
    hk_NNk->Write();
    hpi_NNpi->Write();
    hr->Write();
    hz->Write();
    hjt->Write();

    hr_ptlow->Write();
    hr_ptmed->Write();
    hr_pthigh->Write();

    hz_ptlow->Write();
    hz_ptmed->Write();
    hz_pthigh->Write();

    hjt_ptlow->Write();
    hjt_ptmed->Write();
    hjt_pthigh->Write();

    outfile->Write();
    outfile->Close();

    delete outfile;
    
    TCanvas *c0 = new TCanvas("c0");

    TLegend *leg_z = new TLegend(0.6,0.1,0.9,0.3);
    leg_z->SetTextSize(0.03);
    TLegend *leg_jt = new TLegend(0.1,0.7,0.4,0.9);
    leg_jt->SetTextSize(0.03);
    TLegend *leg_r = new TLegend(0.6,0.7,0.9,0.9);
    leg_r->SetTextSize(0.03);

    TLatex *latex = new TLatex();    
    latex->SetNDC();
    latex->SetTextSize(0.04);
    latex->SetTextFont(22); 
    
    hp_NNp->Draw("E1");
    latex->DrawLatex(0.4, 0.4, "LHCb Open Data");
    c0->Print("output/hp_NNp.pdf");
    hk_NNk->Draw("E1");
    latex->DrawLatex(0.4, 0.4, "LHCb Open Data");
    c0->Print("output/hk_NNk.pdf");
    hpi_NNpi->Draw("E1");
    latex->DrawLatex(0.4, 0.4, "LHCb Open Data");
    c0->Print("output/hpi_NNpi.pdf");

    hr->Draw("E1");
    latex->DrawLatex(0.4, 0.3, "LHCb Open Data");
    c0->Print("output/hr.pdf");

    hr_ptlow->Draw("E1");
    hr_ptmed->SetLineColor(kBlack);
    hr_ptmed->SetMarkerColor(kBlack);
    hr_ptmed->Draw("E1,same");
    hr_pthigh->SetLineColor(kRed);
    hr_pthigh->SetMarkerColor(kRed);
    hr_pthigh->Draw("E1,same");
    leg_r->AddEntry(hr_ptlow.GetPtr(),"20 < #it{p_{T,jet}} < 30 GeV/c","le");
    leg_r->AddEntry(hr_ptmed.GetPtr(),"30 < #it{p_{T,jet}} < 50 GeV/c","le");
    leg_r->AddEntry(hr_pthigh.GetPtr(),"50 < #it{p_{T,jet}} < 100 GeV/c","le");
    leg_r->Draw();
    latex->DrawLatex(0.4, 0.3, "LHCb Open Data");
    c0->Print("output/hr_ptbinned.pdf");
    
    hz->Draw("E1");
    c0->SetLogy();
    c0->SetLogx();
    latex->DrawLatex(0.4, 0.4, "LHCb Open Data");
    c0->Print("output/hz.pdf");   
    
    hz_ptlow->Draw("E1");
    hz_ptmed->SetLineColor(kBlack);
    hz_ptmed->SetMarkerColor(kBlack);
    hz_ptmed->Draw("E1,same");
    hz_pthigh->SetLineColor(kRed);
    hz_pthigh->SetMarkerColor(kRed);
    hz_pthigh->Draw("E1,same");
    leg_z->AddEntry(hz_ptlow.GetPtr(),"20 < #it{p_{T,jet}} < 30 GeV/c","le");
    leg_z->AddEntry(hz_ptmed.GetPtr(),"30 < #it{p_{T,jet}} < 50 GeV/c","le");
    leg_z->AddEntry(hz_pthigh.GetPtr(),"50 < #it{p_{T,jet}} < 100 GeV/c","le");
    leg_z->Draw();
    latex->DrawLatex(0.4, 0.4, "LHCb Open Data");
    c0->Print("output/hz_ptbinned.pdf");
    
    hjt->Draw("E1");
    latex->DrawLatex(0.4, 0.4, "LHCb Open Data");
    c0->Print("output/hjt.pdf");

    hjt_ptlow->Draw("E1");
    hjt_ptmed->SetLineColor(kBlack);
    hjt_ptmed->SetMarkerColor(kBlack);
    hjt_ptmed->Draw("E1,same");
    hjt_pthigh->SetLineColor(kRed);
    hjt_pthigh->SetMarkerColor(kRed);
    hjt_pthigh->Draw("E1,same");
    leg_jt->AddEntry(hjt_ptlow.GetPtr(),"20 < #it{p_{T,jet}} < 30 GeV/c","le");
    leg_jt->AddEntry(hjt_ptmed.GetPtr(),"30 < #it{p_{T,jet}} < 50 GeV/c","le");
    leg_jt->AddEntry(hjt_pthigh.GetPtr(),"50 < #it{p_{T,jet}} < 100 GeV/c","le");
    leg_jt->Draw();
    latex->DrawLatex(0.4, 0.4, "LHCb Open Data");
    c0->Print("output/hjt_ptbinned.pdf");
}