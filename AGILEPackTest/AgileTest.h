#include "AthenaBaseComps/AthAlgorithm.h"

class AgileTest : public AthAlgorithm 
{
    public:
        AgileTest(const std::string& name, ISvcLocator* pSvcLocator);
        StatusCode initialize();
        StatusCode execute();
        StatusCode finalize();

    private:
        std::string m_data;
        std::string m_ntuple;
        std::string m_calib;
};
