#include <iostream>
#include "openmm/Context.h"
#include "openmm/OpenMMException.h"
#include "openmm/internal/ContextImpl.h"
#include "openmm/kernels.h"
#include "openmm/ControlTools.h"


using namespace OpenMM;


ControlTools::ControlTools(std::vector<std::string> tools):toolNames(tools)
{
	temperature = 0.0;
	tauT = 0.0;
	deltaT = 0.0;
	tempValue = 0.0;
}

ControlTools::ControlTools(std::vector<std::string> toolnames, double temperature,
                           double deltaT,Vec3 startPoint, Vec3 endPoint,
                           double tauT,int nBins,int writeInterval)
:toolNames(toolnames),temperature(temperature),
startPoint_(startPoint),endPoint_(endPoint),
deltaT(deltaT),tauT(tauT),nBins_(nBins),writeInterval_(writeInterval)
{
    binTemperature_ = new double[nBins_];
    
    //calculate values for appropriate variables
    Vec3 diff = Vec3(endPoint_[0] - startPoint_[0],endPoint_[1] - startPoint_[1],endPoint_[2] - startPoint_[2]);
    double diffmag = mag(diff);
    unitVector_ = OpenMM::Vec3(diff[0]/diffmag,diff[1]/diffmag,diff[2]/diffmag);
    rSEMag_ = diffmag;
    binWidth_ = diffmag/(double) nBins_;
    
    for(int i=0;i<nBins_;i++)
        binTemperature_[i] = 0.0f;
}

ControlTools::~ControlTools()
{
    std::cout<<"Destructor: ControlTools\n";
    if(binTemperature_!=NULL)
        delete binTemperature_;
}
std::vector<std::string> ControlTools::getKernelNames()
{
	return toolNames;
}
void ControlTools::initialize(ContextImpl& impl)
{
	for(int i=0;i<this->getToolSize();i++)
	{
		this->kernels.push_back(impl.getPlatform().createKernel(toolNames[i],impl));
	}

	//now initialize the kernels for the list of tool names whose kernels are created above
	for(int k = 0;k<this->getKernelSize();k++)
	{
		dynamic_cast<Controls&>(kernels[k].getImpl()).initialize(impl);
	}

}

void ControlTools::controlBeforeForces(ContextImpl& impl)
{
	for(int k=0;k<this->getKernelSize();k++)
	{
		dynamic_cast<Controls&>(kernels[k].getImpl()).controlBeforeForces(impl);
	}
}
void ControlTools::controlAfterForces(ContextImpl& impl)
{
	for(int k=0;k<this->getKernelSize();k++)
	{
		dynamic_cast<Controls&>(kernels[k].getImpl()).controlAfterForces(impl);
	}
}
double ControlTools::mag(OpenMM::Vec3& point){
    double magsqr = ((point[0]*point[0])+(point[1]*point[1])+(point[2]*point[2]));
    double root = sqrt(magsqr);
    return root;
}

