

## Or continue from the previous tutorial

- If you finished building the Tensoflow for C using Bazel, you can continue from the previous tutorial.
- follow instructions [here](https://www.tensorflow.org/install/lang_c/)
- once you confirm that it works, then try the code inside 'inference_frozen_model.cpp' file.
- Compile the code using the following command:
```bash
g++ -std=c++11 -I/usr/local/include -L/usr/local/lib inference_frozen_model.cpp -ltensorflow -o inference_frozen_model
```

- Or for windows, use the following command:
```bash
g++ -std=c++11 -I"C:\tensorflow\include" -L"C:\tensorflow\lib" inference_frozen_model.cpp -ltensorflow -o inference_frozen_model
```

just make sure to replace the path with the correct path to the tensorflow library that you installed from [here](https://www.tensorflow.org/install/lang_c/)
- Run the code using the following command:
```bash
./inference_frozen_model
```

- Or for windows, use the following command:
```bash
.\inference_frozen_model
```

- If you have any issues, please let me know



