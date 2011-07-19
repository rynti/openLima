#ifndef OPENLIMA_UTIL_IREADER_HPP
#define OPENLIMA_UTIL_IREADER_HPP

/**
 * Marks a class as an IReader, most commonly used to define friend classes for read object.
 * They normally have a static method like read(char* filename)
 */
template <typename T>
class IReader {
private:
	IReader();
};

#endif /* OPENLIMA_UTIL_IREADER_HPP */