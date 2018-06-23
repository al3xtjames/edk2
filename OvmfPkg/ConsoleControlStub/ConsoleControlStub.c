/** @file
  EFI_CONSOLE_CONTROL_PROTOCOL stub implementation.

  Copyright (c) 2014, Reza Jelveh. All rights reserved.<BR>

  This program and the accompanying materials are licensed and made
  available under the terms and conditions of the BSD License which
  accompanies this distribution. The full text of the license may be
  found at http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS"
  BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER
  EXPRESS OR IMPLIED.
**/

#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/ConsoleControl.h>

EFI_STATUS
EFIAPI
ConsoleControlGetModeStub (
  IN  EFI_CONSOLE_CONTROL_PROTOCOL    *This,
  OUT EFI_CONSOLE_CONTROL_SCREEN_MODE *Mode,
  OUT BOOLEAN                         *GopUgaExists, OPTIONAL
  OUT BOOLEAN                         *StdInLocked OPTIONAL
  )
{
  *Mode = EfiConsoleControlScreenGraphics;

  if (GopUgaExists != NULL) {
    *GopUgaExists = TRUE;
  }

  if (StdInLocked != NULL) {
    *StdInLocked = TRUE;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ConsoleControlSetModeStub (
  IN EFI_CONSOLE_CONTROL_PROTOCOL    *This,
  IN EFI_CONSOLE_CONTROL_SCREEN_MODE Mode
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ConsoleControlLockStdInStub (
  IN EFI_CONSOLE_CONTROL_PROTOCOL *This,
  IN CHAR16                       *Password
  )
{
  return EFI_SUCCESS;
}

EFI_CONSOLE_CONTROL_PROTOCOL mConsoleControlProtocolStub = {
  ConsoleControlGetModeStub,
  ConsoleControlSetModeStub,
  ConsoleControlLockStdInStub
};

EFI_STATUS
EFIAPI
ConsoleControlStubStart (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS Status;

  Status = gBS->LocateProtocol (
                  &gEfiConsoleControlProtocolGuid,
                  NULL,
                  (VOID **)NULL
                  );

  if (EFI_ERROR (Status)) {
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &ImageHandle,
                    &gEfiConsoleControlProtocolGuid,
                    &mConsoleControlProtocolStub,
                    NULL
                    );
  }

  return Status;
}
