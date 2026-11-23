set -e

AUDIO_FLAGS="-audiodev sdl,id=snd0 -machine pcspk-audiodev=snd0"

echo "Select boot medium:"
echo "  1) Floppy (build/main_floppy.img)"
echo "  2) ISO    (build/aphelionos.iso)"
read -r -p "Choice [1/2]: " choice

case "$choice" in
    1)
        exec qemu-system-x86_64 -fda build/main_floppy.img $AUDIO_FLAGS
        ;;
    2)
        exec qemu-system-x86_64 -cdrom build/aphelionos.iso -boot d $AUDIO_FLAGS
        ;;
    *)
        echo "Invalid choice. Please enter 1 or 2."
        exit 1
        ;;
esac