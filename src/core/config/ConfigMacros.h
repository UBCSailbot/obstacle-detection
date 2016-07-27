#ifndef OBSTACLE_DETECTION_CONFIGMACROS_H
#define OBSTACLE_DETECTION_CONFIGMACROS_H

/**
 * Start defining a nested section of a config file.
 * The name provided as an argument must match exactly
 * the name of the section in the config file.
 *
 * Must be followed by END_CONFIG(name) for the definition of
 * the config section to be complete.
 */
#define START_CONFIG_SECTION(name) \
class name ## _config { \
private: \
    const dlib::config_reader &config_; \
public: \
    name ## _config(const dlib::config_reader &reader) : config_(reader) {} \

/**
 * End the definition of the nested section of a config file
 * with the given name.
 */
#define END_CONFIG_SECTION(name) \
}; \
name ## _config name() const { \
    return name ## _config(config_.block(#name)); \
}

/**
 * Add a definition for a config field that takes a required string value.
 *
 * "Required" here means that an exception will be thrown if an attempt is made to access this
 * field when the field is not specified in the config file being parsed. However, if the field
 * is never accessed, then it doesn't matter whether the field is included in the config file.
 *
 * Required string-type fields get their own macro because string is the default type returned by
 * the config parser, so the implementation is trivial. For required fields of other types,
 * see ADD_COMPLEX_FIELD.
 *
 * If the config field is nested in the config file, this definition should be scoped
 * accordingly.
 */
#define ADD_REQUIRED_STRING_FIELD(name) \
std::string name() const { \
    return config_[#name]; \
}

/**
 * Add a definition for a config field that takes a default value of any type.
 * If the config field is nested in the config file, this definition should be scoped
 * accordingly.
 */
#define ADD_DEFAULT_FIELD(name, defaultValue) \
decltype(defaultValue) name() const { \
    return dlib::get_option(config_, #name, defaultValue); \
}

/**
 * Add a *declaration only* for a config field of the given name and type.
 * Fields added in this way require an explicit implementation in a .cpp file,
 * and as such may or may not be required to have explicit values in the config
 * file (depending on the implementation).
 */
#define ADD_COMPLEX_FIELD(name, type) \
type name() const;

#endif //OBSTACLE_DETECTION_CONFIGMACROS_H
