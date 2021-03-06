//++
// Copyright (c) 2006, Intel Corporation. All rights reserved.<BR>
// This program and the accompanying materials                          
// are licensed and made available under the terms and conditions of the BSD License         
// which accompanies this distribution.  The full text of the license may be found at        
// http://opensource.org/licenses/bsd-license.php                                            
//                                                                                           
// THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
// WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             
// 
//  Module Name:
//
//    EsalLib.s
//
//  Abstract:
//
//
// Revision History:
//
//--

.file  "EsalLib.s"

#include  "IpfMacro.i"

//
// Exports
//
.globl GetEsalEntryPoint


//-----------------------------------------------------------------------------
//++
// GetEsalEntryPoint
//
// Return Esal global and PSR register.
//
// On Entry :
//
//
// Return Value:
//        r8  = EFI_SAL_SUCCESS
//        r9  = Physical Plabel
//        r10 = Virtual Plabel
//        r11 = psr
// 
// As per static calling conventions. 
// 
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY (GetEsalEntryPoint)

      NESTED_SETUP (0,8,0,0)

EsalCalcStart:
      mov   r8  = ip;;
      add   r8  = (EsalEntryPoint - EsalCalcStart), r8;;
      mov   r9  = r8;;
      add   r10 = 0x10, r8;;
      mov   r11 = psr;;
      mov   r8  = r0;;

      NESTED_RETURN

PROCEDURE_EXIT (GetEsalEntryPoint)





//-----------------------------------------------------------------------------
//++
// SetEsalPhysicalEntryPoint
//
// Set the dispatcher entry point
//
// On Entry:
//  in0 = Physical address of Esal Dispatcher
//  in1 = Physical GP
//
// Return Value: 
//   r8 = EFI_SAL_SUCCESS
// 
// As per static calling conventions. 
// 
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY (SetEsalPhysicalEntryPoint)

      NESTED_SETUP (2,8,0,0)

EsalCalcStart1:
      mov   r8   = ip;;
      add   r8   = (EsalEntryPoint - EsalCalcStart1), r8;;
      st8   [r8] = in0;;
      add   r8   = 0x08, r8;;
      st8   [r8] = in1;;
      mov   r8   = r0;;

      NESTED_RETURN

PROCEDURE_EXIT (SetEsalPhysicalEntryPoint)


//-----------------------------------------------------------------------------
//++
// SetEsalVirtualEntryPoint
//
// Register physical address of Esal globals.
//
// On Entry :
//  in0 = Virtual address of Esal Dispatcher
//  in1 = Virtual GP
//
// Return Value: 
//  r8 = EFI_SAL_ERROR
// 
// As per static calling conventions. 
// 
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY (SetEsalVirtualEntryPoint)

      NESTED_SETUP (2,8,0,0)

EsalCalcStart2:
      mov   r8   = ip;;
      add   r8   = (EsalEntryPoint - EsalCalcStart2), r8;;
      add   r8   = 0x10, r8;;
      st8   [r8] = in0;;
      add   r8   = 0x08, r8;;
      st8   [r8] = in1;;
      mov   r8   = r0;;

      NESTED_RETURN

PROCEDURE_EXIT (SetEsalVirtualEntryPoint)




.align 32
EsalEntryPoint: 
    data8 0   // Physical Entry
    data8 0   //         GP
    data8 0   // Virtual Entry
    data8 0   //         GP


