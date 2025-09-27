/**
 * Definition of exception types and error handling primitives.
 *
 * @copyright 2024 ADC Automotive Distance Control Systems GmbH / Continental Corporation
 *
 * @author Ralph Tandetzky <ralph.tandetzky@continental-corporation.com>
 *
 * @file
 *
 * @ingroup visu_fundamentals
 */

#ifndef FUN_EXCEPTIONS_H
#define FUN_EXCEPTIONS_H

#include "base_types.h"

#include <exception>
#include <stdexcept>
#include <string>

namespace visu {
namespace fun{
   
/**
 * Holds the file name, function and line number of the source code.
 */
struct SourceInfo{
    /**
     * The source file name.
     *
     * It is either a pointer to a string literal or `nullptr`. Therefore,
     * there is not need to free it.
     */
    const char_t* file{};

    /**
     * The name of the C++ function.
     *
     * It is either a pointer to a string literal or `nullptr`. Therefore,
     * there is not need to free it.
     */
    const char_t* function{};

    /** The line number of the error. */
    i32 line{};
};

/**
 * Creates a soruce information object. 
 * In the release build, this will be an empty object.
 * In the debug build, this will contain the file, function and line
 * information.
 *
 * \post The `file` member of the `SourceInfo` object is equal to the file name
 * where the macro is used, if `NDEBUG` is not defined. Otherwise, it is equal
 * to `nullptr`. \id{VisuSourceInfoMacroFile}
 * \post The `function` member of the `SourceInfo` object is equal to the
 * function name where the macro is used, if `NDEBUG` is not defined. Otherwise,
 * it is equal to `nullptr`. \id{VisuSourceInfoMacroFunction}
 * \post The `line` member of the `SourceInfo` object is equal to the line
 * number where the macro is used, if `NDEBUG` is not defined. Otherwise, it is
 * equal to `0`. \id{VisuSourceInfoMacroLine}
 */

 #ifndef NODEBUG

    #define SOURCE_INFO \
    visu::fun::SourceInfo { \
    __FILE__, __func__, __LINE__    \   
    }
 #else
    #define SOURCE_INFO visu::fun::SourceInfo {}
 #endif

 /**
 * Exception class that contains a message, source information and possibly
 * nested exceptions.
 */
class Exception
    : public std::runtime_error
    , std::nested_exception {

public: 

    /**
     * Constructor.
     *
     * @param message The message of the exception.
     * @param sourceInfo The source information of the exception.
     *
     * The constructor will also capture the currently caught exception,
     * if any, through the `std::nested_exception` base class.
     *
     * \post `what()` returns the `message`.
     *       \id{VisuExceptionContainsTheCorrectMessageWithString}
     * \post `getSourceInfo()` returns the `sourceInfo`.
     *       \id{VisuExceptionContainsTheCorrectSourceInfoWithString}
     * \post `nested_ptr()` returns the nested exception.
     *       \id{VisuExceptionContainsTheCorrectNestedExceptionWithString}
     */

    explicit Exception(const char *message, const SourceInfo &sourceInfo) noexcept
    : std::runtime_error(message)
    , std::nested_exception{}
    , mSourceInfo(sourceInfo) {}


    /**
     * @returns the source information of the exception.
     *
     * \post The returned value is equal to the `sourceInfo` parameter of the
     * constructor. \id{VisuExceptionContainsTheCorrectSourceInfo}
     */
    SourceInfo getSourceInfo() const noexcept {
        return mSourceInfo;
    }

private:
    /** The source location information of where the exception was thrown. */
    const SourceInfo mSourceInfo;

};

/**
 * \throws an exception of type `Exception` with the given message and source
 * information. \id{VisuThrowExceptionMacro}
 *
 * @param message The message of the exception.
 *
 * # Example
 *
 * ```cpp
 *  f32 mySqrt(f32 x) {
 *      if (x < 0.0f) {
 *          VISU_THROW_EXCEPTION("Cannot take the square root of a negative number.");
 *      }
 *      return std::sqrt(x);
 *  }
 * ```
 *
 * In the above example, it may be more appropriate to use `VISU_ENFORCE()`.
 */
#define VISU_THROW_EXCEPTION(message) throw ::visu::fun::Exception(message, SOURCE_INFO)

/**
 * @throws an exception of type `Exception` _if_ the condition is _not_ met.
 * \id{VisuEnforceMacro}
 *
 * Otherwise nothing is done. This macro is useful for checking preconditions
 * and postconditions. It is similar to `assert()`, but it throws an exception
 * instead of calling `abort()`. The condition argument is evaluated exactly
 * once. Therefore, it is okay to use this macro with functions that have side
 * effects.
 *
 * @param condition The condition to be checked.
 *
 * @post The condition is met or an exception is thrown.
 * @post The condition is evaluated exactly once independent of the value
 *       of the condition. \id{VisuEnforeMacroEvaluatesConditionExactlyOnce}
 *
 * # Example
 *
 * ```cpp
 *  f32 mySqrt(f32 x) {
 *      VISU_ENFORCE(x >= 0.0f);
 *      return std::sqrt(x);
 *  }
 * ```
 */

 #define VISU_ENFORCE(condition) \
    (static_cast<bool>(condition) \
        ? static_cast<void>(0): VISU_THROW_EXCEPTION("Condition is not met: \"" #condition "\"."))

/**
 * @throws an exception of type `Exception` with the given message _if_ the
 * condition is _not_ met. \id{VisuEnforceMsgMacro}
 *
 * Otherwise nothing is done. This macro is useful for checking preconditions
 * and postconditions. It is similar to `VISU_ENFORCE()` but allows for a
 * custom error message. The condition argument is evaluated exactly once.
 * Therefore, it is okay to use this macro with functions that have side
 * effects.
 *
 * @param condition The condition to be checked.
 * @param message The message of the exception to be thrown if the condition is
 *        not met.
 *
 * @post The condition is met or an exception is thrown with the given message.
 * @post The condition is evaluated exactly once independent of the value
 *       of the condition. \id{VisuEnforeMsgMacroEvaluatesConditionExactlyOnce}
 *
 * # Example
 *
 * ```cpp
 *  f32 mySqrt(f32 x) {
 *      VISU_ENFORCE_MSG(
 *          x >= 0.0f, "Cannot take the square root of a negative number.");
 *      return std::sqrt(x);
 *  }
 * ```
 */

 #define VISU_ENFORCE_MSG(condition, message) \
    (static_cast<bool>(condition) ? static_cast<void>(0) : VISU_THROW_EXCEPTION(message))

/**
 * Adds context to an exception by wrapping the execution of a function and
 * throwing a new exception with additional source information if an exception
 * occurs. \id{VisuAddExceptionContext}
 *
 * @tparam F The type of the function to be executed.
 * @param message The message of the exception to be thrown if an exception occurs.
 * @param sourceInfo The source information to be included in the exception.
 * @param f The function to be executed.
 * @returns The result of the function `f` if it executes successfully.
 * @throws Exception if the function `f` throws an exception, with the provided
 *         message and source information.
 *
 * # Example
 *
 * ```cpp
 *  int my_func(int arg) {
 *      return addExceptionContext("Failed to open file", VISU_SOURCE_INFO, [&]() {
 *          // Code that may throw an exception.
 *          int result = other_func(arg);
 *          return result;
 *      });
 *  }
 * ```
 *
 * In the above example, the `addExceptionContext()` function will execute
 * the lambda function and return its result if no exception is thrown. If an
 * exception is thrown, the `addExceptionContext()` function will catch the
 * exception, wrap it in a new exception with the provided message and source
 * information, and rethrow the new exception.
 *
 * It may be more convenient to use the `VISU_ADD_EXCEPTION_CONTEXT()` macro.
 */
template <typename F>
decltype(auto) addExceptionContext(const char* message, const SourceInfo& sourceInfo, F&& f) {
    try {
        return f();
    }
    catch (...) {
        throw visu::fun::Exception(message, sourceInfo);
    }
}

namespace detail {

/**
 * Helper class to add context to an exception.
 *
 * This should not be used by client code. Instead, use the
 * `VISU_ADD_EXCEPTION_CONTEXT()` macro.
 */
class ContextAdder {
public:
    /** Constructor. */
    ContextAdder(const char* message, const SourceInfo& sourceInfo)
        : mMessage(message)
        , mSourceInfo(sourceInfo) {}

    /**
     * Delete compiler generated copy constructor.
     */
    ContextAdder(const ContextAdder&) = delete;

    /**
     * Delete compiler generated assignment operator.
     */
    ContextAdder& operator=(const ContextAdder&) = delete;

    /**
     * Adds context to an exception by wrapping the execution of a function and
     * throwing a new exception with additional source information if an exception
     * occurs.
     *
     * @tparam F The type of the function to be executed.
     * @param f The function to be executed.
     * @returns The result of the function `f` if it executes successfully.
     * @throws Exception if the function `f` throws an exception, with the provided
     *         message and source information.
     */
    template <typename F>
    decltype(auto) operator<<(F&& f) {
        return addExceptionContext(mMessage, mSourceInfo, std::forward<F>(f));
    }

private:
    /** The error message. */
    const char* mMessage;

    /** The source location information of the thrown exception. */
    const SourceInfo& mSourceInfo;
};

}  // namespace detail

/**
 * Adds context to an exception by wrapping the execution of a function and
 * throwing a new exception with additional source information if an exception
 * occurs. \id{VisuAddExceptionContextMacro}
 *
 * @param message The message of the exception to be thrown if an exception occurs.
 *
 * # Example
 *
 * ```cpp
 *  int my_func(int arg) {
 *      return VISU_ADD_EXCEPTION_CONTEXT("Failed to open file.") {
 *          // Code that may throw an exception.
 *          int result = other_func(arg);
 *          return result;
 *      }; // Note: This semicolon is necessary, unfortunately.
 *  }
 * ```
 */
#define VISU_ADD_EXCEPTION_CONTEXT(message) \
    ::visu::fun::detail::ContextAdder(message, VISU_SOURCE_INFO) << [&]()

/**
 * Logs the currently caught exception. \id{LogException}
 *
 * This function is intended to be used in a catch block to log the currently
 * caught exception. It will log the exception message, source information and
 * nested exceptions, if any. Nested exceptions will also be logged.
 */
void logException();

/**
 * Executes a function and logs errors, if it fails.
 * \id{HandleFailuresByLogging}
 *
 * @tparam F The type of the function to be executed.
 * @param f The function to be executed.
 *
 * @returns if the function succeeded (no exception has been thrown).
 */
template <typename F>
bool handleFailuresByLogging(F&& f) {
    try {
        f();
        return true;
    }
    catch (...) {
        logException();
        return false;
    }
}

}  // namespace fun
}  // namespace visu

#endif