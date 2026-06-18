#include <ROOT/RDataFrame.hxx>
#include <iostream>

void inspect_columns() {
    // Load the file into an RDataFrame
    ROOT::RDataFrame df("dijets/DecayTree", "root://eospublic.cern.ch//eos/opendata/lhcb/upload/opendata-lhcb-ntupling-service/analysis-productions/merge-requests/6000/outputs/real-production/00392998_00000001_1.dvntuple.root");

    // Fetch and print the list of column names
    auto columns = df.GetColumnNames();
    for (const auto& col : columns) {
        std::cout << col << std::endl;
    }
}
