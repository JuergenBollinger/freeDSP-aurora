#ifndef QLOWSHELV_HPP
#define QLOWSHELV_HPP

#include <QWidget>
#include "QDspBlock.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QLowShelv;
}

class QLowShelv : public QDspBlock
{
  Q_OBJECT

private:
  enum
  {
    kB0 = 0,
    kB1,
    kB2,
    kA1,
    kA2
  };

  enum
  {
    kParamB2 = 0,
    kParamB1,
    kParamB0,
    kParamA2,
    kParamA1,
    kNumParams
  };

public:
  explicit QLowShelv( double gain, double freq, double slope,
                      uint16_t addrB2, uint16_t addrB1, uint16_t addrB0,
                      uint16_t addrA2, uint16_t addrA1,
                      Vektorraum::tfloat samplerate,
                      CFreeDspAurora* ptrdsp,  QWidget *parent = nullptr );
  ~QLowShelv();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void )
  {
    return H;
  }

  void update( Vektorraum::tvector<Vektorraum::tfloat> f );

  virtual void getUserParams( QByteArray* userParams );

  virtual void setUserParams( QByteArray& userParams, int& idx );

  unsigned int numParameter( void )
  {
    return kNumParams;
  }

  virtual void sendDspParameter( void );

  virtual uint32_t getNumBytes( void );

  virtual void writeDspParameter( void );

private:
  void updateCoeffs( void );

private slots:
  void on_doubleSpinBoxGain_valueChanged( double  );
  void on_doubleSpinBoxFc_valueChanged( double  );
  void on_doubleSpinBoxS_valueChanged( double  );
  void on_pushButtonBypass_clicked();

private:
  Ui::QLowShelv *ui;
  Vektorraum::tfloat fc;
  Vektorraum::tfloat S;
  Vektorraum::tfloat V0;
  Vektorraum::tfloat coeffs[5];
  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp = nullptr;
};

#endif // QLOWSHELV_HPP