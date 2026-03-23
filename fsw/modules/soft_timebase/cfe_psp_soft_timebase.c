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
 *
 * A PSP module that instantiates an RTOS-backed OSAL timebase to provide
 * various timing services.  This in turn may be used to drive CFE TIME 1Hz
 * signal, the CFS SCH major/minor frame sync and other periodic services
 * in CFE.
 *
 * This module can be used on systems which do not have a hardware
 * source for the 1Hz signal or timing info (i.e. simulation, test
 * and debug platforms, etc).
 */

#include "cfe_psp.h"
#include "cfe_psp_module.h"
#include "cfe_psp_config.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(soft_timebase);

/*
 * Global state data for this module (not exposed publicly)
 */
static struct
{
    osal_id_t sys_timebase_id;
} PSP_SoftTimebase_Global;

void soft_timebase_Init(uint32 PspModuleId)
{
    int32 status;

    memset(&PSP_SoftTimebase_Global, 0, sizeof(PSP_SoftTimebase_Global));

    /* Set up the OSAL timebase using the well-known name */
    status = OS_TimeBaseCreate(&PSP_SoftTimebase_Global.sys_timebase_id, CFE_PSP_SOFT_TIMEBASE_NAME, NULL);

#ifndef CFE_SIM_STEPPING
    /*
     * Default behavior: Start a wall-clock-driven periodic timebase.
     * In normal operation, this provides the system-wide timing reference.
     */
    if (status == OS_SUCCESS)
    {
        /* Set the timebase to trigger with desired resolution */
        status = OS_TimeBaseSet(PSP_SoftTimebase_Global.sys_timebase_id, CFE_PSP_SOFT_TIMEBASE_PERIOD,
                                CFE_PSP_SOFT_TIMEBASE_PERIOD);
    }
#else
    /*
     * Simulated stepping mode: DO NOT start the periodic wall-clock timebase.
     *
     * When CFE_SIM_STEPPING is enabled, simulated time is managed by the
     * PSP sim_stepping core module, which controls time advancement explicitly
     * via stepping commands. Starting a wall-clock-driven periodic timebase here
     * would create a competing time source that conflicts with deterministic
     * stepping semantics.
     *
     * The timebase object is created (via OS_TimeBaseCreate) for discovery
     * purposes, but OS_TimeBaseSet is NOT called, so no periodic scheduling
     * occurs. Time retrieval in stepping mode is sourced from the sim_stepping
     * module via the ESA_Stepping_Hook_GetTime() path in
     * timebase_posix_clock.c.
     */
    if (status == OS_SUCCESS)
    {
        printf("CFE_PSP: Created software timebase \'%s\' (stepping mode - wall-clock scheduling disabled)\n",
               CFE_PSP_SOFT_TIMEBASE_NAME);
    }
#endif

    /*
     * The only way this can fail is through a misconfiguration or API incompatibility -
     * if it fails, it means all timing related functions are likely to be broken,
     * CFE TIME may not work correctly, and background jobs will not run.
     *
     * Might even be worth a CFE_PSP_Panic(), but it still may be possible
     * to boot CFE and (maybe) save the system by uploading a file with the bug fixed.
     */
    if (status != OS_SUCCESS)
    {
        printf("CFE_PSP: *** Failed to configure software timebase \'%s\', status = %d! ***\n",
               CFE_PSP_SOFT_TIMEBASE_NAME, (int)status);
    }
#ifndef CFE_SIM_STEPPING
    else
    {
        /* Inform the user that this module is in use */
        printf("CFE_PSP: Instantiated software timebase \'%s\' running at %lu usec\n", CFE_PSP_SOFT_TIMEBASE_NAME,
               (unsigned long)CFE_PSP_SOFT_TIMEBASE_PERIOD);
    }
#endif
}
