#include<string>

//FrontEnd electronics struct
struct HBFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
};

struct HEFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
};

struct HFFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
};

struct HOFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
};

//Backend electronics struct
struct HBBackEnd
{
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
  int ufedid;
};

struct HEBackEnd
{
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
  int ufedid;
};

struct HFBackEnd
{
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
  int ufedid;
};

struct HOBackEnd
{
  double block_coupler;
  int crate, htr, htr_fiber, fiber_ch;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  //int ucrate, uhtr, uhtr_fiber, fiber_ch;
};

//PMT boxes struct
struct HBPMTBox
{};
struct HEPMTBox
{};
struct HFPMTBox
{};
struct HOPMTBox
{
  int sector;
  int pixel;
  std::string letter_code;
};

//Geometry struct
struct HBGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

struct HEGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

struct HFGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

struct HOGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

//Trigger tower struct
struct HBTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

struct HETriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

struct HFTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

struct HOTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};
