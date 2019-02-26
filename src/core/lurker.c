
#include <string.h>

#include "lurker.h"
#include "hal.h"

#define MAX_BUF_SIZE        512
#define TIMEOUT_MS          500

int32_t lurker_main()
{
    int32_t ret = 0;
    lurker_object_t *object[2];
    uint8_t buf[MAX_BUF_SIZE];

    object[0] = get_kernel_object(0);
    object[1] = get_server_object(1);

    do
    {
        memset(buf, 0x00, sizeof(buf));

        ret = connection_recv(buf, MAX_BUF_SIZE, TIMEOUT_MS);

        if (ret > 0) { //well receive something here
            ret = lurker_handle_request(object[0], buf, ret);
        }

        lurker_delay(100);
    } while (1);

    out:
    return ret;
}