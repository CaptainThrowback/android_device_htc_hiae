/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void common_properties()
{
    property_set("rild.libargs", "-d /dev/smd0");
    property_set("ro.ril.hsdpa.category", "14");
    property_set("ro.ril.hsxpa", "4");
    property_set("ro.ril.disable.cpc", "1");
}

void cdma_properties(char const default_cdma_sub[], char const default_network[])
{
    property_set("ro.telephony.default_cdma_sub", default_cdma_sub);
    property_set("ro.telephony.default_network", default_network);

    property_set("telephony.lteOnCdmaDevice", "1");
    property_set("ro.ril.svdo", "true");
    property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420");
    property_set("ro.ril.enable.sdr", "0");
    property_set("ro.ril.enable.gea3", "1");
    property_set("ro.ril.enable.a53", "1");
    property_set("ro.ril.enable.r8fd", "1");
    property_set("persist.radio.snapshot_enabled", "1");
    property_set("persist.radio.snapshot_timer", "22");
}

void gsm_properties(char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);
    property_set("telephony.lteOnGsmDevice", "1");
}

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char bootmid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    property_get("ro.boot.mid", bootmid);

    if (strstr(bootmid, "2PQ930000")) {
        /* hiae_whl (Sprint) */
        cdma_properties("1", "8");
        property_set("ro.build.product", "htc_hiaewhl");
        property_set("ro.product.model", "2PQ93");
        property_set("ro.product.device", "htc_hiaewhl");
    } else if (strstr(bootmid, "2PQ910000")) {
        /* hiae_uhl (Europe) */
        property_set("ro.build.product", "htc_hiaeuhl");
        property_set("ro.build.fingerprint", "HTC/htc_hiaeuhl/htc_hiaeuhl:6.0/MRA58K/buildteam10132347:user/release-keys");
        property_set("ro.product.device", "htc_hiaeuhl");
        property_set("ro.product.model", "HTC One A9");
        property_set("ro.telephony.default_network", "9");
        property_set("telephony.lteOnGsmDevice", "1");
    } else {
        /* hiae_ul (GSM) */
        property_set("ro.build.product", "htc_hiaeul");
        property_set("ro.build.fingerprint", "htc/hiaeul_00502/htc_hiaeul:6.0/MRA58K/635081.3:user/release-keys");
        property_set("ro.product.device", "htc_hiaeul");
        property_set("ro.product.model", "HTC One A9");
        property_set("ro.telephony.default_network", "9");
        property_set("telephony.lteOnGsmDevice", "1");
    }

    property_get("ro.product.device", device);
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid, device);
}
