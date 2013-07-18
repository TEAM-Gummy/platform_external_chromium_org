// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/search/instant_tab.h"
#include "chrome/browser/ui/webui/ntp/ntp_user_data_logger.h"
#include "content/public/browser/web_contents.h"

InstantTab::InstantTab(InstantPage::Delegate* delegate,
                       bool is_incognito)
    : InstantPage(delegate, "", is_incognito) {
}

InstantTab::~InstantTab() {
}

void InstantTab::Init(content::WebContents* contents) {
  SetContents(contents);
}

// static
void InstantTab::CountMouseover(content::WebContents* contents) {
  NTPUserDataLogger* data = NTPUserDataLogger::FromWebContents(contents);
  if (data)
    data->increment_number_of_mouseovers();
}

// static
void InstantTab::EmitMouseoverCount(content::WebContents* contents) {
  NTPUserDataLogger* data = NTPUserDataLogger::FromWebContents(contents);
  if (data)
    data->EmitMouseoverCount();
}

bool InstantTab::ShouldProcessAboutToNavigateMainFrame() {
  return true;
}

bool InstantTab::ShouldProcessFocusOmnibox() {
  return true;
}

bool InstantTab::ShouldProcessNavigateToURL() {
  return true;
}

bool InstantTab::ShouldProcessDeleteMostVisitedItem() {
  return true;
}

bool InstantTab::ShouldProcessUndoMostVisitedDeletion() {
  return true;
}

bool InstantTab::ShouldProcessUndoAllMostVisitedDeletions() {
  return true;
}