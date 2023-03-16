/**
 * \file IfxEray_PinMap.c
 * \brief ERAY I/O map
 * \ingroup IfxLld_Eray
 *
 * \version iLLD_1_0_1_11_0
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Use of this file is subject to the terms of use agreed between (i) you or 
 * the company in which ordinary course of business you are acting and (ii) 
 * Infineon Technologies AG or its licensees. If and as long as no such 
 * terms of use are agreed, use of this file is subject to following:


 * Boost Software License - Version 1.0 - August 17th, 2003

 * Permission is hereby granted, free of charge, to any person or 
 * organization obtaining a copy of the software and accompanying 
 * documentation covered by this license (the "Software") to use, reproduce,
 * display, distribute, execute, and transmit the Software, and to prepare
 * derivative works of the Software, and to permit third-parties to whom the 
 * Software is furnished to do so, all subject to the following:

 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE 
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.

 *
 */

#include "IfxEray_PinMap.h"

IfxEray_Rxd_In IfxEray0_RXDA0_P14_8_IN = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P14, 8}, Ifx_RxSel_a};
IfxEray_Rxd_In IfxEray0_RXDA1_P11_9_IN = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P11, 9}, Ifx_RxSel_b};
IfxEray_Rxd_In IfxEray0_RXDA2_P02_1_IN = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P02, 1}, Ifx_RxSel_c};
IfxEray_Rxd_In IfxEray0_RXDA3_P14_1_IN = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P14, 1}, Ifx_RxSel_d};
IfxEray_Rxd_In IfxEray0_RXDB0_P14_7_IN = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P14, 7}, Ifx_RxSel_a};
IfxEray_Rxd_In IfxEray0_RXDB1_P11_10_IN = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P11,10}, Ifx_RxSel_b};
IfxEray_Rxd_In IfxEray0_RXDB2_P02_3_IN = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P02, 3}, Ifx_RxSel_c};
IfxEray_Rxd_In IfxEray0_RXDB3_P14_1_IN = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P14, 1}, Ifx_RxSel_d};
IfxEray_Txd_Out IfxEray0_TXDA_P02_0_OUT = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P02, 0}, IfxPort_OutputIdx_alt6};
IfxEray_Txd_Out IfxEray0_TXDA_P11_3_OUT = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P11, 3}, IfxPort_OutputIdx_alt4};
IfxEray_Txd_Out IfxEray0_TXDA_P14_0_OUT = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P14, 0}, IfxPort_OutputIdx_alt3};
IfxEray_Txd_Out IfxEray0_TXDA_P14_10_OUT = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P14,10}, IfxPort_OutputIdx_alt6};
IfxEray_Txd_Out IfxEray0_TXDB_P02_2_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P02, 2}, IfxPort_OutputIdx_alt6};
IfxEray_Txd_Out IfxEray0_TXDB_P11_12_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P11,12}, IfxPort_OutputIdx_alt4};
IfxEray_Txd_Out IfxEray0_TXDB_P14_0_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P14, 0}, IfxPort_OutputIdx_alt4};
IfxEray_Txd_Out IfxEray0_TXDB_P14_5_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P14, 5}, IfxPort_OutputIdx_alt6};
IfxEray_Txen_Out IfxEray0_TXENA_P02_4_OUT = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P02, 4}, IfxPort_OutputIdx_alt6};
IfxEray_Txen_Out IfxEray0_TXENA_P11_6_OUT = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P11, 6}, IfxPort_OutputIdx_alt4};
IfxEray_Txen_Out IfxEray0_TXENA_P14_9_OUT = {&MODULE_ERAY0, IfxEray_NodeId_a, {&MODULE_P14, 9}, IfxPort_OutputIdx_alt6};
IfxEray_Txen_Out IfxEray0_TXENB_P02_5_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P02, 5}, IfxPort_OutputIdx_alt6};
IfxEray_Txen_Out IfxEray0_TXENB_P11_11_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P11,11}, IfxPort_OutputIdx_alt6};
IfxEray_Txen_Out IfxEray0_TXENB_P11_6_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P11, 6}, IfxPort_OutputIdx_alt2};
IfxEray_Txen_Out IfxEray0_TXENB_P14_6_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P14, 6}, IfxPort_OutputIdx_alt6};
IfxEray_Txen_Out IfxEray0_TXENB_P14_9_OUT = {&MODULE_ERAY0, IfxEray_NodeId_b, {&MODULE_P14, 9}, IfxPort_OutputIdx_alt5};


const IfxEray_Rxd_In *IfxEray_Rxd_In_pinTable[IFXERAY_PINMAP_NUM_MODULES][IFXERAY_PINMAP_NUM_NODES][IFXERAY_PINMAP_RXD_IN_NUM_ITEMS] = {
    {
        {
            &IfxEray0_RXDA0_P14_8_IN,
            &IfxEray0_RXDA1_P11_9_IN,
            &IfxEray0_RXDA2_P02_1_IN,
            &IfxEray0_RXDA3_P14_1_IN
        },
        {
            &IfxEray0_RXDB0_P14_7_IN,
            &IfxEray0_RXDB1_P11_10_IN,
            &IfxEray0_RXDB2_P02_3_IN,
            &IfxEray0_RXDB3_P14_1_IN
        }
    }
};

const IfxEray_Txd_Out *IfxEray_Txd_Out_pinTable[IFXERAY_PINMAP_NUM_MODULES][IFXERAY_PINMAP_NUM_NODES][IFXERAY_PINMAP_TXD_OUT_NUM_ITEMS] = {
    {
        {
            &IfxEray0_TXDA_P02_0_OUT,
            &IfxEray0_TXDA_P11_3_OUT,
            &IfxEray0_TXDA_P14_0_OUT,
            &IfxEray0_TXDA_P14_10_OUT
        },
        {
            &IfxEray0_TXDB_P02_2_OUT,
            &IfxEray0_TXDB_P11_12_OUT,
            &IfxEray0_TXDB_P14_0_OUT,
            &IfxEray0_TXDB_P14_5_OUT
        }
    }
};

const IfxEray_Txen_Out *IfxEray_Txen_Out_pinTable[IFXERAY_PINMAP_NUM_MODULES][IFXERAY_PINMAP_NUM_NODES][IFXERAY_PINMAP_TXEN_OUT_NUM_ITEMS] = {
    {
        {
            &IfxEray0_TXENA_P02_4_OUT,
            &IfxEray0_TXENA_P11_6_OUT,
            &IfxEray0_TXENA_P14_9_OUT,
            NULL_PTR,
            NULL_PTR
        },
        {
            &IfxEray0_TXENB_P02_5_OUT,
            &IfxEray0_TXENB_P11_6_OUT,
            &IfxEray0_TXENB_P11_11_OUT,
            &IfxEray0_TXENB_P14_6_OUT,
            &IfxEray0_TXENB_P14_9_OUT
        }
    }
};
