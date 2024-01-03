# Error C++

[![build status](https://img.shields.io/github/actions/workflow/status/threeal/errors-cpp/build.yaml?branch=main)](https://github.com/threeal/errors-cpp/actions/workflows/build.yaml)
[![test status](https://img.shields.io/github/actions/workflow/status/threeal/errors-cpp/test.yaml?branch=main&&label=test)](https://github.com/threeal/errors-cpp/actions/workflows/test.yaml)
[![deploy status](https://img.shields.io/github/actions/workflow/status/threeal/errors-cpp/deploy.yaml?branch=main&label=deploy)](https://github.com/threeal/errors-cpp/actions/workflows/deploy.yaml)

Error C++ is a [C++](https://isocpp.org/) package that provides utilities for error handling.
This package mainly consists of the `errors::Error` class, representing an object that may contain an error.

This package serves as an alternative to error handling using [try-catch exceptions](https://en.cppreference.com/w/cpp/language/try_catch), commonly found in C++ code.
It facilitates error handling by returning values, following the style of [Go's error handling](https://go.dev/blog/error-handling-and-go).

## License

This project is licensed under the terms of the [MIT License](./LICENSE).

Copyright © 2023-2024 [Alfi Maulana](https://github.com/threeal)
