/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdint.h>

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#endif

__attribute__((aligned(2)))
const uint8_t c_bmpSmallWhiteDot[] = {

  /*Pixel format: Blue: 5 bit, Green: 6 bit, Red: 5 bit*/
    0x00, 0x00, 0x08, 0x42, 0x9a, 0xd6, 0x9e, 0xf7, 0x18, 0xc6, 0x8a, 0x52, 0x00, 0x00, 
    0x8a, 0x52, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8a, 0x52,  
    0x18, 0xc6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0xf7,  
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,  
    0x1c, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9a, 0xd6,  
    0x8a, 0x52, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8e, 0x73,  
    0x00, 0x00, 0x8e, 0x73, 0x1c, 0xe7, 0xff, 0xff, 0x1c, 0xe7, 0x8e, 0x73, 0x00, 0x00,  

};

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
