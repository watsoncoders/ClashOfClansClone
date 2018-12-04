/**
 * @module cocos2dx_baseframework
 */
var fr = fr || {};

/**
 * @class CustomClass
 */
fr.CustomClass = {

/**
 * @method initWithFile
 * @param {char} arg0
 * @return {bool}
 */
initWithFile : function (
char 
)
{
    return false;
},

/**
 * @method create
 * @param {String} arg0
 * @return {fr.CustomClass}
 */
create : function (
str 
)
{
    return fr.CustomClass;
},

};

/**
 * @class FrameworkDelegate
 */
fr.FrameworkDelegate = {

/**
 * @method applicationFinished
 */
applicationFinished : function (
)
{
},

/**
 * @method applicationDidEnterBackground
 */
applicationDidEnterBackground : function (
)
{
},

/**
 * @method applicationWillEnterForeground
 */
applicationWillEnterForeground : function (
)
{
},

/**
 * @method applicationDidFinishLaunching
 * @return {bool}
 */
applicationDidFinishLaunching : function (
)
{
    return false;
},

/**
 * @method getInstance
 * @return {fr.FrameworkDelegate}
 */
getInstance : function (
)
{
    return fr.FrameworkDelegate;
},

/**
 * @method FrameworkDelegate
 * @constructor
 */
FrameworkDelegate : function (
)
{
},

};

/**
 * @class sPackage
 */
fr.sPackage = {

/**
 * @method sPackage
 * @constructor
 */
sPackage : function (
)
{
},

};

/**
 * @class InPacket
 */
fr.InPacket = {

/**
 * @method getDouble
 * @return {double}
 */
getDouble : function (
)
{
    return 0;
},

/**
 * @method getCmdId
 * @return {int}
 */
getCmdId : function (
)
{
    return 0;
},

/**
 * @method getByte
 * @return {int}
 */
getByte : function (
)
{
    return 0;
},

/**
 * @method getError
 * @return {int}
 */
getError : function (
)
{
    return 0;
},

/**
 * @method getLong
 * @return {long long}
 */
getLong : function (
)
{
    return long long;
},

/**
 * @method getBool
 * @return {bool}
 */
getBool : function (
)
{
    return false;
},

/**
 * @method getInt
 * @return {int}
 */
getInt : function (
)
{
    return 0;
},

/**
 * @method init
 * @param {fr.sPackage} arg0
 */
init : function (
spackage 
)
{
},

/**
 * @method getControllerId
 * @return {int}
 */
getControllerId : function (
)
{
    return 0;
},

/**
 * @method getString
 * @return {String}
 */
getString : function (
)
{
    return ;
},

/**
 * @method getUnsignedShort
 * @return {unsigned short}
 */
getUnsignedShort : function (
)
{
    return 0;
},

/**
 * @method getShort
 * @return {int}
 */
getShort : function (
)
{
    return 0;
},

/**
 * @method getCharArray
 * @param {int} arg0
 * @return {char}
 */
getCharArray : function (
int 
)
{
    return 0;
},

/**
 * @method getBytes
 * @param {int} arg0
 * @return {char}
 */
getBytes : function (
int 
)
{
    return 0;
},

/**
 * @method InPacket
 * @constructor
 */
InPacket : function (
)
{
},

};

/**
 * @class OutPacket
 */
fr.OutPacket = {

/**
 * @method reset
 */
reset : function (
)
{
},

/**
 * @method putInt
 * @param {int} arg0
 * @return {fr.OutPacket}
 */
putInt : function (
int 
)
{
    return fr.OutPacket;
},

/**
 * @method setCmdId
 * @param {int} arg0
 */
setCmdId : function (
int 
)
{
},

/**
 * @method packHeader
 */
packHeader : function (
)
{
},

/**
 * @method setControllerId
 * @param {int} arg0
 */
setControllerId : function (
int 
)
{
},

/**
 * @method putUnsignedShort
 * @param {unsigned short} arg0
 * @return {fr.OutPacket}
 */
putUnsignedShort : function (
short 
)
{
    return fr.OutPacket;
},

/**
 * @method putShort
 * @param {int} arg0
 * @return {fr.OutPacket}
 */
putShort : function (
int 
)
{
    return fr.OutPacket;
},

/**
 * @method putString
 * @param {String} arg0
 * @return {fr.OutPacket}
 */
putString : function (
str 
)
{
    return fr.OutPacket;
},

/**
 * @method initData
 * @param {int} arg0
 */
initData : function (
int 
)
{
},

/**
 * @method putBytes
 * @param {char} arg0
 * @param {int} arg1
 * @return {fr.OutPacket}
 */
putBytes : function (
char, 
int 
)
{
    return fr.OutPacket;
},

/**
 * @method putLong
 * @param {long long} arg0
 * @return {fr.OutPacket}
 */
putLong : function (
)
{
    return fr.OutPacket;
},

/**
 * @method updateSize
 */
updateSize : function (
)
{
},

/**
 * @method getData
 * @param {int} arg0
 * @return {char}
 */
getData : function (
int 
)
{
    return 0;
},

/**
 * @method putByteArray
 * @param {char} arg0
 * @param {int} arg1
 * @return {fr.OutPacket}
 */
putByteArray : function (
char, 
int 
)
{
    return fr.OutPacket;
},

/**
 * @method putByte
 * @param {int} arg0
 * @return {fr.OutPacket}
 */
putByte : function (
int 
)
{
    return fr.OutPacket;
},

/**
 * @method updateUnsignedShortAtPos
 * @param {unsigned short} arg0
 * @param {int} arg1
 */
updateUnsignedShortAtPos : function (
short, 
int 
)
{
},

/**
 * @method OutPacket
 * @constructor
 */
OutPacket : function (
)
{
},

};

/**
 * @class GsnClient
 */
fr.GsnClient = {

/**
 * @method onSubThreadStarted
 */
onSubThreadStarted : function (
)
{
},

/**
 * @method onSubThreadEnded
 */
onSubThreadEnded : function (
)
{
},

/**
 * @method setTimeoutForRead
 * @param {int} arg0
 */
setTimeoutForRead : function (
int 
)
{
},

/**
 * @method disconnect
 */
disconnect : function (
)
{
},

/**
 * @method setReceiveDataListener
 * @param {function} arg0
 */
setReceiveDataListener : function (
func 
)
{
},

/**
 * @method isDoConnection
 * @return {bool}
 */
isDoConnection : function (
)
{
    return false;
},

/**
 * @method initThread
 * @return {bool}
 */
initThread : function (
)
{
    return false;
},

/**
 * @method setTimeoutForConnect
 * @param {int} arg0
 */
setTimeoutForConnect : function (
int 
)
{
},

/**
 * @method createSocket
 */
createSocket : function (
)
{
},

/**
 * @method onSubThreadLoop
 */
onSubThreadLoop : function (
)
{
},

/**
 * @method getTimeoutForRead
 * @return {int}
 */
getTimeoutForRead : function (
)
{
    return 0;
},

/**
 * @method setFinishConnectListener
 * @param {function} arg0
 */
setFinishConnectListener : function (
func 
)
{
},

/**
 * @method onUIThreadReceiveMessage
 * @param {fr.sPackage} arg0
 */
onUIThreadReceiveMessage : function (
spackage 
)
{
},

/**
 * @method setDisconnectListener
 * @param {function} arg0
 */
setDisconnectListener : function (
func 
)
{
},

/**
 * @method setListener
 * @param {fr.ClientListener} arg0
 */
setListener : function (
clientlistener 
)
{
},

/**
 * @method getTimeoutForConnect
 * @return {int}
 */
getTimeoutForConnect : function (
)
{
    return 0;
},

/**
 * @method connect
 * @param {char} arg0
 * @param {int} arg1
 */
connect : function (
char, 
int 
)
{
},

/**
 * @method reconnect
 * @return {bool}
 */
reconnect : function (
)
{
    return false;
},

/**
 * @method clearQueue
 */
clearQueue : function (
)
{
},

/**
 * @method send
 * @param {fr.OutPacket} arg0
 */
send : function (
outpacket 
)
{
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method create
 * @return {fr.GsnClient}
 */
create : function (
)
{
    return fr.GsnClient;
},

/**
 * @method getInstance
 * @return {fr.GsnClient}
 */
getInstance : function (
)
{
    return fr.GsnClient;
},

/**
 * @method GsnClient
 * @constructor
 */
GsnClient : function (
)
{
},

};
