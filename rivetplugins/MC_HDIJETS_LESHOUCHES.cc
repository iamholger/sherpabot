// -*- C++ -*-
#include "Rivet/Analyses/MC_JetAnalysis.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Tools/ParticleIdUtils.hh"
#include <map>
#include <sstream>

namespace Rivet {

  struct Hist_Info {
    size_t bins;
    double min,max;
    Hist_Info(size_t b, double mn, double mx) : bins(b),min(mn),max(mx) {}
  };
  typedef std::pair<std::string,Hist_Info> StrHistInfo;

  /// @brief MC validation analysis for higgs [-> tau tau] + jets events
  class MC_HDIJETS_LESHOUCHES : public Analysis {
  private:
    double _jeta, _jR, _jpT, _jjdy, _jjmass;
    std::vector<double> _j1pTs;
    //std::map<std::string,AIDA::IHistogram1D *> histos, jetvetohistos;
    std::map<std::string,Histo1DPtr> histos, jetvetohistos;
  public:
    MC_HDIJETS_LESHOUCHES() : 
      Analysis("MC_HDIJETS_LESHOUCHES"),
      _jeta(5.), _jR(0.4), _jpT(30.), _jjdy(2.8), _jjmass(400.)
    {}

    void init() {
      FinalState fs;
      IdentifiedFinalState hfinder(-10.,10.,0.*GeV);
      hfinder.acceptId(PID::HIGGS);
      VetoedFinalState hexcl(FinalState(-_jeta,_jeta,0.*GeV));
      hexcl.addVetoDetail(PID::HIGGS,0.*GeV,14000.*GeV);
      addProjection(hfinder, "Hfinder");
      addProjection(FastJets(hexcl, FastJets::ANTIKT, _jR), "Jets");

      inithistos();
    }


    void inithistos() {
      // inclusive and one-jet observables
      histos["H_pT_incl"]    = bookHisto1D("H_pT_incl",60,0.,300.);
      histos["H_y_incl"]     = bookHisto1D("H_y_incl",20,-5.,5.);
      histos["NJet_incl"]    = bookHisto1D("NJet_incl",5,-0.5,4.5);
      histos["jet1_pT_incl"] = bookHisto1D("jet1_pT_incl",60,0.,300.);
      histos["jet1_y_incl"]  = bookHisto1D("jet1_y_incl",20,-5.,5.);
      // dijet observables -> needed four times
      std::vector<StrHistInfo> obs;
      obs.push_back(StrHistInfo(std::string("H_pT_"),
                                Hist_Info(60,0.,300.)));
      obs.push_back(StrHistInfo(std::string("jet1_pT_"),
                                Hist_Info(60,0.,300.)));
      obs.push_back(StrHistInfo(std::string("jet2_pT_"),
                                Hist_Info(60,0.,300.)));
      obs.push_back(StrHistInfo(std::string("jet3_pT_"),
                                Hist_Info(60,0.,300.)));
      obs.push_back(StrHistInfo(std::string("H_y_"),
                                Hist_Info(20,-5.,5.)));
      obs.push_back(StrHistInfo(std::string("jet1_y_"),
                                Hist_Info(20,-5.,5.)));
      obs.push_back(StrHistInfo(std::string("jet2_y_"),
                                Hist_Info(20,-5.,5.)));
      obs.push_back(StrHistInfo(std::string("jet3_y_"),
                                Hist_Info(20,-5.,5.)));
      obs.push_back(StrHistInfo(std::string("jet3_ystar_"),
                                Hist_Info(20,-5.,5.)));
      obs.push_back(StrHistInfo(std::string("jet12_dy_"),
                                Hist_Info(20,0.,10.)));
      obs.push_back(StrHistInfo(std::string("jet12_dphi_"),
                                Hist_Info(20,0.,PI)));
      obs.push_back(StrHistInfo(std::string("jet12_mass_"),
                                Hist_Info(25,0.,1000.)));
      obs.push_back(StrHistInfo(std::string("H_jet12_pT_"),
                                Hist_Info(20,0.,300.)));
      obs.push_back(StrHistInfo(std::string("H_jet12_dphi_"),
                                Hist_Info(20,0.,PI)));
      obs.push_back(StrHistInfo(std::string("H_jet12_ystar_"),
                                Hist_Info(20,0.,10.)));
      std::vector<std::string> type;
      type.push_back("dijet_");
      type.push_back("VBF_");
      for (char choice('A');choice<'C';++choice) {
        std::string c(&choice); c=c.substr(0,1);
        for (size_t j(0);j<type.size();++j) {
          for (size_t i(0);i<obs.size();++i) {
            std::string label(obs[i].first+type[j]+c);
            histos[label] = bookHisto1D(label,
                                            obs[i].second.bins,
                                            obs[i].second.min,
                                            obs[i].second.max);
          }
        }
        // [0] incl XS, [1] 2 tagjets XS, [2] 3rd jet XS,
        // [3] VBF cuts XS, [4] 3rd jet in VBF cuts XS
        std::string cf("cutflow_");
        histos[cf+c] = bookHisto1D(cf+c,5,-0.5,4.5);
        // [0] dijet XS, [1] h within tagjets XS,
        // [2] VBF cuts XS, [3] h within tagjets XS
        std::string hw("XS_H_within_tagjets_");
        histos[hw+c] = bookHisto1D(hw+c,4,-0.5,3.5);
      }
    }

    /// Do the analysis
    void analyze(const Event & e) {
      const IdentifiedFinalState hfinder = 
        applyProjection<IdentifiedFinalState>(e, "Hfinder");
      if (hfinder.size()!=1) vetoEvent;
      const double weight = e.weight();

      histos["cutflow_A"]->fill(0.,weight); // cutflow[0] -> incl.xsec
      histos["cutflow_B"]->fill(0.,weight); // cutflow[0] -> incl.xsec

      // define h-momentum and jets
      const Particle& higgs(hfinder.particles()[0]);
      const FastJets& jetpro = applyProjection<FastJets>(e, "Jets");
      const Jets& jets = jetpro.jetsByPt(_jpT*GeV);

      // inclusive observables
      histos["H_pT_incl"]->fill(higgs.momentum().pT(),weight);
      histos["H_y_incl"]->fill(higgs.momentum().rapidity(),weight);
      for (size_t i(0);i<5;++i) {
        if (jets.size()>=i) histos["NJet_incl"]->fill(i,weight);
      }
      // one jet observables
      if (jets.size()>0) {
        histos["jet1_pT_incl"]->fill(jets[0].momentum().pT(),weight);
        histos["jet1_y_incl"]->fill(jets[0].momentum().rapidity(),weight);
      }
      // define tagging jets
      if (jets.size()>1) {
        for (char choice('A');choice<'C';++choice) {
	  std::string c(&choice); c=c.substr(0,1);
          const Jet * tagjet1 = &jets[0];
          const Jet * tagjet2 = &jets[1];
          if (choice=='B') { // choice 'B' forward-backward
            for (size_t i(0);i<jets.size();++i) {
              if (jets[i].momentum().rapidity()
                    < tagjet1->momentum().rapidity()) {
                tagjet1 = &jets[i];
              }
              else if (jets[i].momentum().rapidity()
                         > tagjet2->momentum().rapidity()) {
                tagjet2 = &jets[i];
              }
            }
            // sanity check
            for (size_t i(0);i<jets.size();++i) {
              if (jets[i].momentum().rapidity() 
                    < tagjet1->momentum().rapidity()) {
                std::cout << "ERROR: minimal rapidity not found.\n";
              }
              if (jets[i].momentum().rapidity()
                    > tagjet2->momentum().rapidity()) {
                std::cout << "ERROR: maximal rapidity not found.\n";
              }
            }
            if (tagjet1->momentum().pT() < tagjet2->momentum().pT()) {
              std::swap(tagjet1,tagjet2);
            }
          }
          AnalyseConfiguration(higgs,*tagjet1,*tagjet2,jets,c,weight);
        }
      }
    }

    void AnalyseConfiguration(const Particle& higgs, const Jet& jet1,
                              const Jet& jet2, const Jets& jets,
                              const std::string& c, const double& weight) {
      // h ........ Higgs
      // jet1 ..... leading tagjet (in either definition A or B)
      // jet2 ..... subleading tagjet (in either definition A or B)
      // jets ..... all jets to find suitably defined third jet
      // c ........ either 'A' or 'B'
      // weight ... weight of the event
      //
      // dijet observables
      const FourMomentum& h = higgs.momentum();
      const FourMomentum& j1 = jet1.momentum();
      const FourMomentum& j2 = jet2.momentum();
      histos["cutflow_"+c]->fill(1.,weight); // cutflow[1] -> 2 tagjets
      FillHiggsWithinDijetsHisto(h.rapidity(),j1.rapidity(),j2.rapidity(),
				 c,0,weight);
      FillDijetHistos(h,j1,j2,c,"dijet",weight);
      if (jets.size()>2) {
        // hardest jet which is non-tagjet, jets are already sorted by pT
        // -> first non-tagjet is hardest
        // -> always find one
        size_t idx(0);
        for (size_t i(0);i<jets.size();++i) {
          if (&jets[i]!=&jet1 && &jets[i]!=&jet2) {
            idx = i;
            break;
          }
        }
        const FourMomentum& j3(jets[idx].momentum());
        histos["cutflow_"+c]->fill(2.,weight); // cutflow[2] -> 3rd jet
	FillThreejetHistos(h,j1,j2,j3,c,"dijet",weight);
      }
      // VBF observables
      if (fabs(j1.rapidity()-j2.rapidity())>_jjdy && (j1+j2).mass()>_jjmass) {
        histos["cutflow_"+c]->fill(3.,weight); // cutflow[3] -> dyjj and mjj
	FillHiggsWithinDijetsHisto(h.rapidity(),j1.rapidity(),j2.rapidity(),
				   c,2,weight);
	FillDijetHistos(h,j1,j2,c,"VBF",weight);
        if (jets.size()>2) {
          // hardest jet which is non-tagjet and inbetween j1 and j2,
          // jets are already sorted by pT -> first non-tagjet is hardest
          // possibility not to find one in choice A -> nothing to do
          size_t idx(0);
          for (size_t i(0);i<jets.size();++i) {
            if (&jets[i]!=&jet1 && &jets[i]!=&jet2) {
              const FourMomentum& j(jets[i].momentum());
              if ((j.rapidity()>j1.rapidity() && j.rapidity()<j2.rapidity()) ||
                  (j.rapidity()<j1.rapidity() && j.rapidity()>j2.rapidity())) {
                idx = i;
                break;
              }
            }
            if (i==jets.size()-1) return;
          }
          const FourMomentum& j3(jets[idx].momentum());
          histos["cutflow_"+c]->fill(4.,weight); // cutflow[4] -> 3rd jet VBF
	  FillThreejetHistos(h,j1,j2,j3,c,"VBF",weight);
        }
      }
    }

    void FillHiggsWithinDijetsHisto(const double& hy, const double& j1y,
				    const double& j2y,
				    const string& c, const size_t& i, 
				    const double& weight) {
      histos["XS_H_within_tagjets_"+c]->fill(i,weight);
      if ((hy>j1y && hy<j2y) || (hy<j1y && hy>j2y)) {
        histos["XS_H_within_tagjets_"+c]->fill(i+1,weight);
      }
    }

    void FillDijetHistos(const FourMomentum& h, const FourMomentum& j1,
			 const FourMomentum& j2,
			 const string& c, const string& type, 
			 const double& weight) {
      double massjj((j1+j2).mass());
      double dyjj(fabs(j1.rapidity()-j2.rapidity()));
      double hystar(fabs(h.rapidity()-(j1.rapidity()+j2.rapidity())/2.));
      histos["H_pT_"+type+"_"+c]->fill(h.pT(),weight);
      histos["H_y_"+type+"_"+c]->fill(h.rapidity(),weight);
      histos["jet1_pT_"+type+"_"+c]->fill(j1.pT(),weight);
      histos["jet1_y_"+type+"_"+c]->fill(j1.rapidity(),weight);
      histos["jet2_pT_"+type+"_"+c]->fill(j2.pT(),weight);
      histos["jet2_y_"+type+"_"+c]->fill(j2.rapidity(),weight);
      histos["jet12_dy_"+type+"_"+c]->fill(dyjj,weight);
      histos["jet12_dphi_"+type+"_"+c]->fill(deltaPhi(j1,j2),weight);
      histos["jet12_mass_"+type+"_"+c]->fill(massjj,weight);
      histos["H_jet12_pT_"+type+"_"+c]->fill((h+j1+j2).pT(),weight);
      histos["H_jet12_dphi_"+type+"_"+c]->fill(deltaPhi(h,j1+j2),weight);
      histos["H_jet12_ystar_"+type+"_"+c]->fill(hystar,weight);
    }

    void FillThreejetHistos(const FourMomentum& h, const FourMomentum& j1,
			    const FourMomentum& j2, const FourMomentum& j3,
			    const string& c, const string& type, 
			    const double& weight) {
      double ystar((j1.rapidity()+j2.rapidity())/2.-j3.rapidity());
      histos["jet3_pT_"+type+"_"+c]->fill(j3.pT(),weight);
      histos["jet3_y_"+type+"_"+c]->fill(j3.rapidity(),weight);
      histos["jet3_ystar_"+type+"_"+c]->fill(ystar,weight);
    }

    /// Finalize
    void finalize() {
      double scalefactor(crossSection()/sumOfWeights());
      for (std::map<std::string,Histo1DPtr>::iterator 
             hit=histos.begin(); hit!=histos.end();hit++) 
        scale(hit->second,scalefactor);
    }
  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(MC_HDIJETS_LESHOUCHES);
}
