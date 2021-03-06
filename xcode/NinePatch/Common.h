/**
 This struct is used for doing pixel-tasting. We get CoreGraphics to create a bitmap context wherein the memory representation looks like this struct, then we cast the pointer to that memory to be of this struct's type. Pretty self-explanatory.
 */
typedef struct _TURGBAPixel {
	UInt8 red;
	UInt8 green;
	UInt8 blue;
	UInt8 alpha;	
} TURGBAPixel;

/**
 Defined here, used as part of the pixel-tasting code. Helps make sure the memory representation of the bitmap context is made up of stuff that looks just like TURGBAPixel.
 */
#define TURGBABytesPerPixel (4)

/**
 This tests if a pixel is black. Here "black" means alpha isn't at zero (AKA: it's at least partially opaque) and r == g == b == 0.
 */
#define TURGBAPixelIsBlack(PIXEL) (((PIXEL.red == 0) && (PIXEL.green == 0) && (PIXEL.blue == 0) && (PIXEL.alpha != 0))?(YES):(NO))

#define TUTruncateBelow(VALUE, FLOOR) ((( VALUE ) < ( FLOOR ))?(( FLOOR )):(( VALUE )))
#define TUTruncateAbove(VALUE, CEILING) ((( VALUE ) > ( CEILING ))?(( CEILING )):(( VALUE )))
#define TUTruncateWithin(VALUE, FLOOR, CEILING) ((( VALUE ) < ( FLOOR ))?(( FLOOR )):((( VALUE ) > ( CEILING ))?(( CEILING )):(( VALUE ))))
#define TUTruncateAtZero(VALUE) TUTruncateBelow(VALUE, 0.0f)

#define TUForceYesOrNo(ABOOL) ((ABOOL)?(YES):(NO))
#define TUYesOrNoString(ABOOL) ((( ABOOL ))?(@"YES"):(@"NO"))

#define TUWithinEpsilon(EPSILON, X, Y) TUForceYesOrNo((((X-Y) > (-1.0f * EPSILON)) || ((X-Y) < EPSILON)))

//#define DEBUG
//#define NP_ASSERTION_CHECKING
//#define IMAGEDEBUG

// DLog is almost a drop-in replacement for NSLog  
// DLog();  
// DLog(@"here");  
// DLog(@"value: %d", x);  
// Unfortunately this doesn't work DLog(aStringVariable); you have to do this instead DLog(@"%@", aStringVariable);  
#ifdef DEBUG  
#define DLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);  
#else  
#define DLog(...)  
#endif  

// ALog always displays output regardless of the DEBUG setting  
#define ALog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);  

#define LLog(STR) DLog(@"%@",STR)

#define NPLogException(E) DLog(@"Caught '%@' < '%@', '%@' >.",[E name],[E reason],[E userInfo])
#define NPLogError(E) DLog(@"Error: '%@', '%@', '%@'.",[E localizedDescription],[E localizedFailureReason],[E localizedRecoveryOptions]);

#ifdef NP_ASSERTION_CHECKING
#define NPLogExceptionRethrowIfAssertionFailure(E) { \
NPLogException(E); \
if (E && [[E name] isEqualToString:NSInternalInconsistencyException]) { \
	@throw E; \
}} 
#else 
#define NPLogExceptionRethrowIfAssertionFailure(E) NPLogException(E)
#endif

#ifdef NP_OUTPUT_LOGGING
#define NPFOutputLog(AFLOAT) DLog(@"returning %s: '%f'.",#AFLOAT,AFLOAT)
#define NPDOutputLog(ANINT) DLog(@"returning %s: '%d'.",#ANINT,ANINT)
#define NPOOutputLog(ANOBJ) DLog(@"returning %s: '%@'.",#ANOBJ,ANOBJ)
#define NPBOutputLog(ABOOL) DLog(@"returning %s: '%@'.",#ABOOL,TUYesOrNoString(ABOOL))
#define NPCGROutputLog(ARECT) DLog(@"returning %s: '%@'.",#ARECT,NSStringFromCGRect(ARECT))
#define NPCGSOutputLog(ASIZE) DLog(@"returning %s: '%@'.",#ASIZE,NSStringFromCGSize(ASIZE))
#define NPCGPOutputLog(APOINT) DLog(@"returning %s: '%@'.",#APOINT,NSStringFromCGPoint(APOINT))
#define NPNSROutputLog(ARANGE) DLog(@"returning %s: '%@'.",#ARANGE,NSStringFromRange(ARANGE))
#else
#define NPFOutputLog(...)  
#define NPDOutputLog(...)  
#define NPOOutputLog(...)  
#define NPBOutputLog(...)  
#define NPCGROutputLog(...) 
#define NPCGSOutputLog(...) 
#define NPCGPOutputLog(...) 
#define NPNSROutputLog(...) 
#endif

#ifdef NP_INPUT_LOGGING
#define NPAInputLog(...) DLog(##__VA_ARGS__)
// convenience input loggers for single-argument messages
#define NPAFInputLog(AFLOAT) DLog(@"%s: '%f'",#AFLOAT,AFLOAT)
#define NPADInputLog(ANINT) DLog(@"%s: '%d'",#ANINT,ANINT)
#define NPAOInputLog(ANOBJ) DLog(@"%s: '%@'",#ANOBJ,ANOBJ)
#define NPABInputLog(ABOOL) DLog(@"%s: '%@'",#ABOOL,TUYesOrNoString(ABOOL))
#else
#define NPAInputLog(...) 
#define NPAFInputLog(AFLOAT) 
#define NPADInputLog(ANINT) 
#define NPAOInputLog(ANOBJ) 
#define NPABInputLog(ABOOL) 
#endif


#ifdef NP_ASSERTION_CHECKING
#define NPParameterAssert(COND) NSParameterAssert(COND)
#define NPCParameterAssert(COND) NSCParameterAssert(COND)
#define NPAssert(COND,DESC) NSAssert(COND,DESC)
#define NPCAssert(COND,DESC) NSCAssert(COND,DESC)
#else
#define NPParameterAssert(...) 
#define NPCParameterAssert(...) 
#define NPAssert(...) 
#define NPCAssert(...) 
#endif

#define STRINGIFY2( x) #x
#define STRINGIFY(x) STRINGIFY2(x)
#define PASTE2( a, b) a##b
#define PASTE( a, b) PASTE2( a, b)
#define PASSTHROUGH(X) X

#define NPOBJCStringOfToken(TOKEN) PASSTHROUGH(PASTE( PASSTHROUGH(@), PASSTHROUGH(STRINGIFY(TOKEN))))

#define NPSelfProperty(PROP) ([self PROP])

#define NPAssertPropertyNonNil(PROP) NPAssert((NPSelfProperty(PROP) != nil), ([NSString stringWithFormat:@"self.%s should never be nil.",( (#PROP) )]))

#define NPParameterAssertNotNilConformsToProtocol(OBJ,PROT) NPParameterAssert((OBJ != nil) && ([OBJ conformsToProtocol:@protocol(PROT)]))
#define NPParameterAssertNotNilIsKindOfClass(OBJ,CLASS) NPParameterAssert((OBJ != nil) && ([OBJ isKindOfClass:[CLASS class]]))

#define NPAssertNilOrConformsToProtocol(OBJ,PROT) NPAssert(((OBJ == nil) || ((OBJ != nil) && [OBJ conformsToProtocol:@protocol(PROT)])),([NSString stringWithFormat:@"Variable %s must either be nil or conform to %s protocol.", ( (#OBJ) ), ( (#PROT) )]))
#define NPAssertNilOrIsKindOfClass(OBJ,CLASS) NPAssert(((OBJ == nil) || ((OBJ != nil) && [OBJ isKindOfClass:[CLASS class]])), ([NSString stringWithFormat:@"Variable %s must either be nil or be kind of %s class.", (#OBJ), (#CLASS)]))

#define NPAssertWithinEpsilon(EPSILON,X,Y) NPAssert( (((X-Y) > (-1.0f * EPSILON)) || ((X-Y) < EPSILON)),([NSString stringWithFormat:@"Should have (%s,%s) within %f but instead (%f,%f).",#X,#Y,EPSILON,X,Y]))
#define NPAssertWithinOne(X,Y) NPAssertWithinEpsilon(1.0f,X,Y)

#define NPAssertThreeSubSizesSumCorrectlyOnOneAxis(AXIS,MASTERSIZE,SIZE_ONE,SIZE_TWO,SIZE_THREE) NPAssertWithinOne(MASTERSIZE.AXIS,( SIZE_ONE.AXIS + SIZE_TWO.AXIS + SIZE_THREE.AXIS ))
#define NPAssertCorrectSubsizeWidthDecomposition(MASTER,SIZE_ONE,SIZE_TWO,SIZE_THREE) NPAssertThreeSubSizesSumCorrectlyOnOneAxis(width, MASTER, SIZE_ONE, SIZE_TWO, SIZE_THREE)
#define NPAssertCorrectSubsizeHeightDecomposition(MASTER,SIZE_ONE,SIZE_TWO,SIZE_THREE) NPAssertThreeSubSizesSumCorrectlyOnOneAxis(height, MASTER, SIZE_ONE, SIZE_TWO, SIZE_THREE)

#define NPAssertCorrectSubimageWidthDecomposition(MASTER,IMAGE_ONE,IMAGE_TWO,IMAGE_THREE) NPAssertCorrectSubsizeWidthDecomposition([MASTER size],[IMAGE_ONE size],[IMAGE_TWO size],[IMAGE_THREE size])
#define NPAssertCorrectSubimageHeightDecomposition(MASTER,IMAGE_ONE,IMAGE_TWO,IMAGE_THREE) NPAssertCorrectSubsizeWidthDecomposition([MASTER size],[IMAGE_ONE size],[IMAGE_TWO size],[IMAGE_THREE size])

#ifdef IMAGEDEBUG
#define IMLog(IMAGE, IMAGENAME) TUImageLog(IMAGE,[[NSString stringWithFormat:@"debugImage.%.0f.%u.",[NSDate timeIntervalSinceReferenceDate],((NSUInteger) rand())] stringByAppendingString:( IMAGENAME )])
#else
#define IMLog(IMAGE, IMAGENAME) 
#endif
