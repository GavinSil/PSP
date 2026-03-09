/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * \file
 * \ingroup  psp
 *
 * Purpose: This file contains PSP-level simulation stepping hooks
 *          that are called to retrieve unified simulation time when CFE_SIM_STEPPING is enabled.
 *
 * These hooks allow simulation stepping implementations to provide deterministic time
 * progression at the PSP level, particularly for timebase module time retrieval operations.
 */

#ifndef CFE_PSP_SIM_STEPPING_H
#define CFE_PSP_SIM_STEPPING_H

/****************************************************************************************
                                     INCLUDE FILES
 ***************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/****************************************************************************************
                            STEPPING HOOK DECLARATIONS
 ***************************************************************************************/

/**
 * \brief Hook to retrieve simulation time when stepping is enabled
 *
 * Called by PSP timebase modules to obtain simulation time instead of wall-clock time
 * when CFE_SIM_STEPPING is enabled. This allows deterministic time progression in
 * simulation/test environments.
 *
 * \param[out]  sim_time_ns    Pointer to store simulation time in nanoseconds since epoch
 *
 * \return  true if simulation time was successfully provided
 * \return  false if hook not implemented or stepping disabled (use wall-clock instead)
 *
 * \note This function is declared but implementations are provided only when
 *       CFE_SIM_STEPPING is defined. When not defined, this becomes a no-op stub
 *       that returns false.
 */
bool CFE_PSP_SimStepping_Hook_GetTime(uint64_t *sim_time_ns);

#endif /* CFE_PSP_SIM_STEPPING_H */
