#!/sbin/sh

SCRIPTNAME="VendorInit"
LOGFILE=/tmp/recovery.log

log_info()
{
	echo "I:$SCRIPTNAME:"$1 >> $LOGFILE
}

log_error()
{
	echo "E:$SCRIPTNAME:"$1 >> $LOGFILE
}

bootmid=$(getprop ro.boot.mid)
bootcid=$(getprop ro.boot.cid)
device=$(getprop ro.product.device)
model=$(getprop ro.product.model)
product=$(getprop ro.build.product)

log_info "Updating device properties based on MID and CID..."
log_info "MID Found: $bootmid"
log_info "CID Found: $bootcid"

case $bootmid in
	"2PQ910000")
		## hiae_uhl (Europe) ##
		log_info "Current product: $product"
		resetprop ro.build.product "htc_hiaeuhl"
		product=$(getprop ro.build.product)
		log_info "New product: $product"
		log_info "Current device: $device"
		resetprop ro.product.device "htc_hiaeuhl"
		device=$(getprop ro.product.device)
		log_info "New device: $device"
		;;
	"2PQ930000")
		## hiae_whl (Sprint) ##
		log_info "Current product: $product"
		resetprop ro.build.product "htc_hiaewhl"
		log_info "New product: $product"
		log_info "Current device: $device"
		resetprop ro.product.device "htc_hiaewhl"
		device=$(getprop ro.product.device)
		log_info "New device: $device"
		log_info "Current model: $model"
		resetprop ro.product.model "2PQ93"
		model=$(getprop ro.product.model)
		log_info "New model: $model"
		;;
	*)
		## hiae_ul (GSM) ##
		log_error "MID not found. Setting default values."
		log_info "Current product: $product"
		resetprop ro.build.product "htc_hiaeul"
		product=$(getprop ro.build.product)
		log_info "New product: $product"
		log_info "Current device: $device"
		resetprop ro.product.device "htc_hiaeul"
		device=$(getprop ro.product.device)
		log_info "New device: $device"
		log_info "Current model: $model"
		;;
esac

exit 0