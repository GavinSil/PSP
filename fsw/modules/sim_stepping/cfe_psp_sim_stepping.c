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

#include "cfe_psp.h"
#include "cfe_psp_module.h"
#include "cfe_psp_sim_stepping.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(sim_stepping);

void sim_stepping_Init(uint32 PspModuleId)
{
    printf("CFE_PSP: Simulation stepping module initialized\n");
}

#ifdef CFE_SIM_STEPPING

bool CFE_PSP_SimStepping_Hook_GetTime(uint64_t *sim_time_ns)
{
    return false;
}

#else

bool CFE_PSP_SimStepping_Hook_GetTime(uint64_t *sim_time_ns)
{
    return false;
}

#endif
