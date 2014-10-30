#include "AGILEPackTest/AgileTest.h"
#include "GaudiKernel/MsgStream.h"

#include "AGILEPack/AGILEPack.h"
#include <iostream>

AgileTest::AgileTest(const std::string& name, ISvcLocator* pSvcLocator) :
AthAlgorithm(name, pSvcLocator)
{
    declareProperty("data", m_data);
    declareProperty("ntuple", m_ntuple);
    declareProperty("calib", m_calib);
}

StatusCode AgileTest::initialize()
{
    ATH_MSG_INFO("initialize()");

    return StatusCode::SUCCESS;
}

StatusCode AgileTest::execute() 
{
    ATH_MSG_INFO("Your new package and algorithm are successfully executing");
    
    ATH_MSG_INFO("#-----------------------------------------------------------");
    ATH_MSG_INFO("# Test running simple AGILEPack Utilities");
    ATH_MSG_INFO("#-----------------------------------------------------------");
    
    std::string name = "   AGILEPack       ";
    ATH_MSG_INFO("The string \'"+name +"\' is trimmed to "+agile::trim(name));
    
    ATH_MSG_INFO("#-----------------------------------------------------------");
    ATH_MSG_INFO("# Test Loading in Data");
    ATH_MSG_INFO("#-----------------------------------------------------------");
    
    // load data
    agile::root::tree_reader reader;
    reader.add_file(m_data, m_ntuple);
    
    // set branches used from the ttree
    reader.set_branch("Hbb", agile::root::integer);
    reader.set_branch("dRBB", agile::root::single_precision);
    reader.set_branch("dEtaBB", agile::root::single_precision);
    reader.set_branch("dPhiVBB", agile::root::single_precision);
    reader.set_branch("dPhiLBmin", agile::root::single_precision);
    reader.set_branch("pTV", agile::root::single_precision);
    reader.set_branch("mBB", agile::root::single_precision);
    reader.set_branch("HT", agile::root::single_precision);
    reader.set_branch("pTB1", agile::root::single_precision);
    reader.set_branch("pTB2", agile::root::single_precision);
    reader.set_branch("mTW", agile::root::single_precision);
    reader.set_branch("pTL", agile::root::single_precision);
    reader.set_branch("MET", agile::root::single_precision);
    reader.set_branch("mLL", agile::root::single_precision);

    // check if the test loaded properly
    agile::dataframe D = reader.get_dataframe(10);
    std::cout << D << std::endl;
    
    ATH_MSG_INFO("#-----------------------------------------------------------");
    ATH_MSG_INFO("# Test AGILEPack Predictions");
    ATH_MSG_INFO("#-----------------------------------------------------------");
    
    // load the neural network
    agile::neural_net* net(new agile::neural_net);
    net->from_yaml(m_calib);
   
    // make predictions
    auto input_vars= net->get_inputs();
    std::map<std::string, double> inputs;

    for(int entry = 0; entry < 10; ++entry)
    {
        std::map<std::string, double> inputs;
        for(auto i : input_vars)
        {
            inputs[i] = D.at(entry, i);
        }
        auto outputs = net->predict_map(inputs);

        std::cout << "Prob[event #" << entry << " == Hbb] = ";
        std::cout << outputs["Hbb"];
        std::cout << "\t Hbb = " << D.at(entry, "Hbb")  << std::endl;
    }


    return StatusCode::SUCCESS;
}

StatusCode AgileTest::finalize()
{
    ATH_MSG_INFO("finalize()");

    return StatusCode::SUCCESS;
}
