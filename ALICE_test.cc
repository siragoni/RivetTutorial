// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"

namespace Rivet {


  /// @brief Add a short analysis description here
  class ALICE_test : public Analysis {
  public:

    /// Constructor
    DEFAULT_RIVET_ANALYSIS_CTOR(ALICE_test);


    /// @name Analysis methods
    //@{

    /// Book histograms and initialise projections before the run
    void init() {

      // Initialise and register projections
      // declare(FinalState(Cuts::abseta < 5 && Cuts::pT > 100*MeV), "FS");

      /// "FS" is the name of our projection
      declare(FinalState(Cuts::abseta < 0.8 && Cuts::pT < 10*GeV), "FS");

      // Book histograms
      //_h_XXXX = bookHisto1D(1, 1, 1);
      //_p_AAAA = bookProfile1D(2, 1, 1);
      //_c_BBBB = bookCounter(3, 1, 1);

      _h_pt = bookHisto1D("histpt", 10, 0., 10.);

    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {

      /// @todo Do the event by event analysis here
      /// event is the param of the function which refers to the projection "FS"
      const FinalState &fs = applyProjection<FinalState>(event, "FS");
      foreach ( const Particle &p, fs.particles() ) {
        double pt = p.pT();
        _h_pt->fill( pt / GeV, event.weight() );
      }


    }


    /// Normalise histograms etc., after the run
    void finalize() {

      // normalize(_h_YYYY); // normalize to unity
      // scale(_h_ZZZZ, crossSection()/picobarn/sumOfWeights()); // norm to cross section
      scale( _h_pt, 1./sumOfWeights() );

    }

    //@}


    /// @name Histograms
    //@{
    Histo1DPtr /*_h_XXXX, _h_YYYY, _h_ZZZZ,*/ _h_pt;
    // Profile1DPtr _p_AAAA;
    // CounterPtr _c_BBBB;
    //@}


  };


  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ALICE_test);


}
