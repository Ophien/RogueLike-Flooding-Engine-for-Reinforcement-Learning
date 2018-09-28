#ifndef OBJECT_H
#define OBJECT_H

namespace simulationCore{
class core;
}

class Object
{
  public:
    Object();
    ~Object();

    virtual void start();
    virtual void update();

    virtual void preupdate();
    virtual void posupdate();

    bool getActive();
    void setActive(bool val);

    void setId(unsigned int _id);
    unsigned int getId();

    void setSimulationCore(simulationCore::core* core);

  private:
    unsigned int id;
    bool active;
  
  protected:
    simulationCore::core* sim;
};

#endif