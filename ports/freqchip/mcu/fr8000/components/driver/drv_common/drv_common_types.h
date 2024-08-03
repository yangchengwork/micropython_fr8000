#ifndef FR_COMMON_TYPES_H
#define FR_COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {    // allow C++ to use these headers
#endif

#ifndef TRUE
#define TRUE    (1)
#endif      // TRUE
#ifndef true
#define true    TRUE
#endif      // true

#ifndef FALSE
#define FALSE   (0)
#endif      // FALSE
#ifndef false
#define false   FALSE
#endif      // false

#ifndef EOF
#define EOF     (-1)
#endif      // EOF

//#ifndef __STDBOOL_H__
//typedef unsigned char bool;
//#endif

#ifndef MIN
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#endif

/****d* include.types/dw_state
 * NAME
 *  dw_state
 * DESCRIPTION
 *  This is a generic data type used for 1-bit wide bitfields which have
 *  a "set/clear" property.  This is used when modifying registers
 *  within a peripheral's memory map.
 * SOURCE
 */
enum fr_state {
    Fr_err = -1,
    Fr_clear = 0,
    Fr_set = 1
};
/*****/
#if 1
enum fr_channel_t {
    FR_CHANNEL_0,
    FR_CHANNEL_1,
    FR_CHANNEL_MAX,
};
#endif

/****d* include.types/dw_callback
 * DESCRIPTION
 *  This is a generic data type used for handling callback functions
 *  with each driver.
 * ARGUMENTS
 *  dev         -- device handle
 *  eCode       -- event/error code
 * NOTES
 *  The usage of the eCode argument is typically negative for an error
 *  code and positive for an event code.
 * SOURCE
 */
typedef void (*fr_callback)(enum fr_channel_t channel, int32_t eCode);
/*****/
 /****d* include.data/dw_dma_mode
 * DESCRIPTION
 *  This is the data type used for enabling software or hardware
 *  handshaking for DMA transfers.  Using software handshaking changes
 *  how an interrupt handler processes Rx full and Tx empty interrupts.
 *  Any DesignWare peripheral which supports DMA transfers has API
 *  function which match those listed below.
 * SEE ALSO
 *  dw_*_setDmaTxMode(), dw_*_setDmaRxMode(), dw_*_getDmaTxMode(),
 *  dw_*_getDmaRxMode(), dw_*_setDmaTxNotifier(),
 *  dw_*_setDmaTxNotifier()
 * SOURCE
 */
 enum fr_dma_mode {
    Fr_dma_none,            // DMA is not being used
    Fr_dma_sw_handshake,    // DMA using software handshaking
    Fr_dma_hw_handshake     // DMA using hardware handshaking
};
   

/****d* include.types/dw_dma_notifier_func
 * DESCRIPTION
 *  This is the data type used for specifying DMA notifier functions.
 *  These are needed when software handshaking is used with peripheral
 *  DMA transfers in order to inform the DMA controller when data is
 *  ready to be sent/received.
 * ARGUMENTS
 *  dev         -- DMA device handle
 *  channel     -- associated channel number
 *  single      -- single or burst transfer?
 *  last        -- is this the last block?
 * NOTES
 *  The single and last arguments are only necessary when the peripheral
 *  involved is also acting as the flow controller.
 * SOURCE
 */
 
 #ifdef CFG_DMA
typedef void (*fr_dma_notifier_func)(enum fr_i2c_channel_t channel, unsigned
        channel, bool single, bool last);
/*****/



/*****/

/****s* include.api/dw_dma_notify
 * DESCRIPTION
 *  This is the data structure used to store a DMA notifier function
 *  and its related arguments.
 * SOURCE
 */
struct fr_dma_config {
    enum dw_dma_mode mode;
    dw_dma_notifier_func notifier;
    struct dw_device *dmac;
    unsigned channel;
};
/*****/
#endif
#ifdef __cplusplus
}
#endif

#endif      // FR_COMMON_TYPES_H

