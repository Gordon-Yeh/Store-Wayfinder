#include "../../Security/tracker.h"
#include "../../GPS/GPS.h"
#include "../tests.h"

static void test_inbound() {
    Bound tb;
    gps_point p;
    int result;
    tb.min_lon = 233.23;
    tb.min_lat = 454.0;
    tb.max_lon = 240.12;
    tb.max_lat = 455.0;

    p.lon = 0;
    p.lat = 0;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, OUT_OF_BOUND);

    p.lon = 233.0;
    p.lat = 454.5;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, OUT_OF_BOUND);

    p.lon = 233.50;
    p.lat = 453.4;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, OUT_OF_BOUND);

    p.lon = 233.50;
    p.lat = 454.4;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, IN_BOUND);

    p.lon = 233.50;
    p.lat = 455.0;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, OUT_OF_BOUND);

    p.lon = 233.50;
    p.lat = 454.99999;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, IN_BOUND);

    p.lon = 233.50;
    p.lat = 454.123;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, IN_BOUND);

    p.lon = 233.75;
    p.lat = 454.99999;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, IN_BOUND);

    /* corner cases */
    p.lon = 233.23;
    p.lat = 454.0;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, OUT_OF_BOUND);

    p.lon = 240.12;
    p.lat = 455.0;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, OUT_OF_BOUND);

    p.lon = 233.23000001;
    p.lat = 454.0000001;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, IN_BOUND);

    p.lon = 240.119999;
    p.lat = 454.999999;
    result = inbound(&p, &tb);
    VALIDATE_INT(result, IN_BOUND);
}

void test_tracker() {
    test_inbound();
}