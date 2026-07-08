#include <ROOT/RDataFrame.hxx>
#include <iostream>

void inspect_columns() {
    // Load the file into an RDataFrame
    ROOT::RDataFrame df("dijets/DecayTree", "root://eospublic.cern.ch//eos/opendata/lhcb/CollisionNtuples/OPENDATA.LHCB.CGFF.E7X9/outputs/real-production/00393007_00000004_1.dvntuple.root");

    // Fetch and print the list of column names
    auto columns = df.GetColumnNames();
    for (const auto& col : columns) {
        std::cout << col << std::endl;
    }
}
