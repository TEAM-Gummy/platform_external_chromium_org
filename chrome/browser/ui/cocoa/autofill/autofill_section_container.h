// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_SECTION_CONTAINER_H_
#define CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_SECTION_CONTAINER_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/autofill/autofill_dialog_types.h"
#import "chrome/browser/ui/cocoa/autofill/autofill_input_field.h"
#import "chrome/browser/ui/cocoa/autofill/autofill_layout.h"

namespace autofill {
  class AutofillDialogController;
}

@class AutofillSectionView;
@class AutofillSuggestionContainer;
@class LayoutView;
@class MenuButton;
@class MenuController;

// Delegate to handle display of validation messages.
@protocol AutofillValidationDisplay

// Updates the validation message for a given field.
- (void)updateMessageForField:(NSControl<AutofillInputField>*)field;

@end


// View controller for a section of the payment details. Contains a label
// describing the section as well as associated inputs and controls. Built
// dynamically based on data retrieved from AutofillDialogController.
@interface AutofillSectionContainer :
    NSViewController<AutofillLayout, AutofillInputDelegate> {
 @private
  base::scoped_nsobject<LayoutView> inputs_;
  base::scoped_nsobject<MenuButton> suggestButton_;
  base::scoped_nsobject<AutofillSuggestionContainer> suggestContainer_;
  base::scoped_nsobject<NSTextField> label_;

  // The view for the container.
  base::scoped_nsobject<AutofillSectionView> view_;

  // List of weak pointers, which constitute unique field IDs.
  std::vector<const autofill::DetailInput*> detailInputs_;

  // A delegate to handle display of validation messages. Not owned.
  id<AutofillValidationDisplay> validationDelegate_;

  base::scoped_nsobject<MenuController> menuController_;
  autofill::DialogSection section_;
  autofill::AutofillDialogController* controller_;  // Not owned.
}

@property(readonly, nonatomic) autofill::DialogSection section;
@property(assign, nonatomic) id<AutofillValidationDisplay> validationDelegate;

// Designated initializer. Queries |controller| for the list of desired input
// fields for |section|.
- (id)initWithController:(autofill::AutofillDialogController*)controller
              forSection:(autofill::DialogSection)section;

// Populates |output| with mappings from field identification to input value.
- (void)getInputs:(autofill::DetailOutputMap*)output;

// Called when the controller-maintained suggestions model has changed.
- (void)modelChanged;

// Called when the contents of a section have changed.
- (void)update;

// Validate this section. Validation rules depend on |validationType|.
- (BOOL)validateFor:(autofill::ValidationType)validationType;

@end

@interface AutofillSectionContainer (ForTesting)
- (NSControl<AutofillInputField>*)getField:(autofill::AutofillFieldType)type;
@end

#endif  // CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_SECTION_CONTAINER_H_