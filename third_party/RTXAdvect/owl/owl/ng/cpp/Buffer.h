// ======================================================================== //
// Copyright 2019 Ingo Wald                                                 //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "RegisteredObject.h"

namespace owl {

  struct Buffer : public RegisteredObject
  {
    typedef std::shared_ptr<Buffer> SP;
    
    Buffer(Context *const context, OWLDataType type);
    
    /*! destructor - free device data, de-regsiter, and destruct */
    virtual ~Buffer() { destroy(); }
    
    virtual std::string toString() const { return "Buffer"; }

    const void *getPointer(int deviceID);

    void resize(size_t newSize);
    void upload(const void *hostPtr);

    /*! destroy whatever resouces this buffer's ll-layer handle this
        may refer to; this will not destruct the current object
        itself, but should already release all its references */
    void destroy();

    OWLDataType type;
  };

  struct HostPinnedBuffer : public Buffer {
    typedef std::shared_ptr<HostPinnedBuffer> SP;
    
    HostPinnedBuffer(Context *const context,
                     OWLDataType type,
                     size_t count);

    /*! pretty-printer, for debugging */
    std::string toString() const override { return "HostPinnedBuffer"; }
  };
  
  struct DeviceBuffer : public Buffer {
    typedef std::shared_ptr<DeviceBuffer> SP;
    
    DeviceBuffer(Context *const context,
                 OWLDataType type,
                 size_t count,
                 const void *init);

    /*! pretty-printer, for debugging */
    std::string toString() const override { return "DeviceBuffer"; }
  };
  
} // ::owl
