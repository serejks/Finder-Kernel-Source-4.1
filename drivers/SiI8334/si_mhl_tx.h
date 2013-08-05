/***********************************************************************************/
/*  Copyright (c) 2009-2010, Silicon Image, Inc.  All rights reserved.             */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1060 East Arques Avenue, Sunnyvale, California 94085                           */
/***********************************************************************************/


//
// structure to hold operating information of MhlTx component
//
//
// structure to hold operating information of MhlTx component
//
typedef struct
{
    bool_t		interruptDriven;	// Remember what app told us about interrupt availability.
    uint8_t	pollIntervalMs;		// Remember what app set the polling frequency as.
    
    uint8_t	status_0;			// Received status from peer is stored here
    uint8_t	status_1;			// Received status from peer is stored here
    
    uint8_t     connectedReady;     // local MHL CONNECTED_RDY register value
    uint8_t     linkMode;           // local MHL LINK_MODE register value
    uint8_t     mhlHpdStatus;       // keep track of SET_HPD/CLR_HPD
    uint8_t     mhlRequestWritePending;
    
    bool_t		mhlConnectionEvent;
    uint8_t	mhlConnected;
    
    uint8_t     mhlHpdRSENflags;       // keep track of SET_HPD/CLR_HPD
    
    // mscMsgArrived == true when a MSC MSG arrives, false when it has been picked up
    bool_t		mscMsgArrived;
    uint8_t	mscMsgSubCommand;
    uint8_t	mscMsgData;
    
    // Remember FEATURE FLAG of the peer to reject app commands if unsupported
    uint8_t	mscFeatureFlag;
    
    uint8_t     cbusReferenceCount;  // keep track of CBUS requests
    // Remember last command, offset that was sent.
    // Mostly for READ_DEVCAP command and other non-MSC_MSG commands
    uint8_t	mscLastCommand;
    uint8_t	mscLastOffset;
    uint8_t	mscLastData;
    
    // Remember last MSC_MSG command (RCPE particularly)
    uint8_t	mscMsgLastCommand;
    uint8_t	mscMsgLastData;
    uint8_t	mscSaveRcpKeyCode;
    
    //  support WRITE_BURST
    uint8_t     localScratchPad[16];
    uint8_t     miscFlags;          // such as SCRATCHPAD_BUSY
    //  uint8_t 	mscData[ 16 ]; 		// What we got back as message data
    #ifdef CONFIG_VENDOR_EDIT
    //added by zhangyue for debugging the Boot Problem(can't boot correctly) on 2011-11-14
    //deleted by zhangyue on 2011-11-22 for concentrating the modified code
    //deleted by zhangyue on 2011-12-16 as Silicon had solved the first abnormal Interrrupt start
    #if 0
    #ifndef mhl_power_dbg
    #define mhl_power_dbg
    #endif
    #ifndef mhl_power_dbg	
    uint8_t	initInt;   //indicate initialization Int has occured. 
    #endif
    //deleted by zhangyue on 2011-11-22 end
    #endif
    //deleted by zhangyue on 2011-12-16 as Silicon had solved the first abnormal Interrrupt end
    #endif
} mhlTx_config_t;


// bits for mhlHpdRSENflags:
typedef enum
{
    MHL_HPD            = 0x01,
    MHL_RSEN           = 0x02
}MhlHpdRSEN_e;

typedef enum
{
    FLAGS_SCRATCHPAD_BUSY         = 0x01,
    FLAGS_REQ_WRT_PENDING         = 0x02,
    FLAGS_WRITE_BURST_PENDING     = 0x04,
    FLAGS_RCP_READY               = 0x08,
    FLAGS_HAVE_DEV_CATEGORY       = 0x10,
    FLAGS_HAVE_DEV_FEATURE_FLAGS  = 0x20,
    FLAGS_SENT_DCAP_RDY           = 0x40,
    FLAGS_SENT_PATH_EN            = 0x80,
}MiscFlags_e;


typedef enum
{
    MSC_STATE_IDLE		        = 0x00, // Until MHL is connected, do nothing
    MSC_STATE_BEGIN		        = 0x01, // Start of MSC engine to read devcap of the peer
    MSC_STATE_POW_DONE	        = 0x02, // Just read devcap[2]. Next do the feature flags
    MSC_STATE_RCP_READY         = 0x03, // Feature flags done. Ready to take in RCP.
}MSC_STATE_e;



