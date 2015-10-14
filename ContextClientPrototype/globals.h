#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

// Enables resp. disables the XSD part int the XML tab
#define XSD_ENABLED false

// XML directory
#define XML_DIR "/home/stefan/Development/ContextRouting/data/XML"

// XSD directory
#define XSD_DIR "/home/stefan/Development/ContextRouting/data/XSD"

// Set XSD files due to validator problem with xml attribute "xmlns"
#define XSD_DICTIONARY "file:/"XSD_DIR"/Dictionary.xsd"
#define XSD_CODING "file:/"XSD_DIR"/ContextCodings.xsd"


#endif /* SRC_GLOBALS_H_ */
