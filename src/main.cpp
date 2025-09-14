#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include <iostream>
int main() {
    try {
        ConverterJSON converter;
        InvertedIndex index;

        std::cout << "Starting search engine: "
            << converter.GetConfig()["config"]["name"] << "\n";
        std::cout << "Max responses: " << converter.GetResponsesLimit() << "\n";

        auto documents = converter.GetTextDocuments();
        if (documents.empty()) {
            std::cerr << "Warning: No documents found for indexing\n";
            return 0;
        }

        std::cout << "Loaded " << documents.size() << " documents\n";
        index.UpdateDocumentBase(documents);

        SearchServer server(index, converter.GetResponsesLimit());

        auto requests = converter.GetRequests();
        if (requests.empty()) {
            std::cout << "No search requests found\n";
            return 0;
        }

        std::cout << "Processing " << requests.size() << " requests...\n";
        auto results = server.search(requests);

        std::vector<std::vector<std::pair<size_t, float>>> convertedResults;
        for (const auto& innerVec : results) {
            std::vector<std::pair<size_t, float>> convertedInner;
            for (const RelativeIndex& relIndex : innerVec) {
                convertedInner.emplace_back(relIndex.doc_id, relIndex.rank);
            }
            convertedResults.push_back(std::move(convertedInner));
        }

        converter.putAnswers(convertedResults);
        std::cout << "Results saved to answers.json\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}