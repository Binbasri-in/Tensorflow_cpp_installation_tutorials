#include <tensorflow/c/c_api.h>
#include <iostream>
#include <vector>
#include <string>

void DeallocateBuffer(void* data, size_t) {
    std::free(data);
}

void Deallocator(void* data, size_t length, void* arg) {
    free(data);
}

static std::vector<TF_Tensor*> CreateInputTensors(const std::vector<float>& input_data) {
    std::vector<TF_Tensor*> input_tensors;
    for (const float input : input_data) {
        const int64_t dims[1] = {1};
        size_t nbytes = sizeof(float);
        float* data = reinterpret_cast<float*>(std::malloc(nbytes));
        *data = input;

        TF_Tensor* tensor = TF_NewTensor(TF_FLOAT, dims, 1, data, nbytes, &Deallocator, nullptr);
        input_tensors.push_back(tensor);
    }
    return input_tensors;
}

int main() {
    // Initialize a TensorFlow session
    TF_Graph* Graph = TF_NewGraph();
    TF_Status* Status = TF_NewStatus();
    TF_SessionOptions* SessionOpts = TF_NewSessionOptions();
    TF_Buffer* RunOpts = nullptr;

    const char* saved_model_dir = "./frozen_models/linear_regression_model.pb";
    const char* tags = "serve"; // Tag used for serving
    int ntags = 1;

    // Load the saved model
    TF_Session* Session = TF_LoadSessionFromSavedModel(SessionOpts, RunOpts, saved_model_dir, &tags, ntags, Graph, nullptr, Status);
    if (TF_GetCode(Status) != TF_OK) {
        std::cerr << "Error loading model: " << TF_Message(Status) << std::endl;
        return 1;
    } else {
        std::cout << "Model loaded successfully" << std::endl;
    }

    // Define input data
    std::vector<float> input_data = {5.0}; // Example input
    std::vector<TF_Tensor*> input_tensors = CreateInputTensors(input_data);

    // Define inputs and outputs
    std::vector<TF_Output> inputs;
    std::vector<TF_Tensor*> input_values;

    TF_Operation* input_op = TF_GraphOperationByName(Graph, "serving_default_input_1");
    if (input_op == nullptr) {
        std::cerr << "Error: Failed to find the input operation." << std::endl;
        return 1;
    }
    TF_Output input = {input_op, 0};
    inputs.push_back(input);
    input_values.push_back(input_tensors[0]); // Assuming single input for simplicity

    std::vector<TF_Output> outputs;
    TF_Operation* output_op = TF_GraphOperationByName(Graph, "StatefulPartitionedCall");
    if (output_op == nullptr) {
        std::cerr << "Error: Failed to find the output operation." << std::endl;
        return 1;
    }
    TF_Output output = {output_op, 0};
    outputs.push_back(output);
    std::vector<TF_Tensor*> output_values(outputs.size(), nullptr);

    // Run the session
    TF_SessionRun(Session, nullptr,
                  &inputs[0], &input_values[0], inputs.size(),
                  &outputs[0], &output_values[0], outputs.size(),
                  nullptr, 0, nullptr, Status);

    if (TF_GetCode(Status) == TF_OK) {
        std::cout << "Session run successfully" << std::endl;
        // Handle output tensor
    } else {
        std::cerr << "Error running session: " << TF_Message(Status) << std::endl;
    }

    // Clean up
    TF_DeleteGraph(Graph);
    TF_DeleteSession(Session, Status);
    TF_DeleteSessionOptions(SessionOpts);
    TF_DeleteStatus(Status);

    return 0;
}
