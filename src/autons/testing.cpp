#include "autons.h"
#include "vex.h"

void Autons::testing()
{
    
}
void Autons::high()
{
    """
    set_coordinates(14.26, -46.871, 340) // Start against the park zone
    drive(22.111, -22.111, 340) // Eat the blocks in the middle
    turn(14, -14, backwards)
    drive(14, -14, 225) // Drive to the center goal
    score_high_center_goal() // Score only preload just to get AWP
    wait(400, msec)

    drive(46.67, -46.67, 225) // In front of loader
    turn(46.67, -58.748) // Could distance reset here, around 180 degrees
    scraper_down()

    drive(46.67, -58.748, 180) // Ram into loader
    wait(1000, msec) // tune to wait long enough to get the right colored blocks and avoid the wrong color
    scraper_up()

    drive(46.67, -30.566, 180) // Line up to long goal
    score_long_goal()

    """
}
void Autons::low()
{
    """
    set_coordinates(-14.26, -46.871, 340) // Start against the park zone
    drive(-22.111, -22.111, 340) // Eat the blocks in the middle
    turn(-14, -14)
    drive(-14, -14, 45) // Drive to the center goal
    score_low_center_goal() // Score only preload just to get AWP
    wait(400, msec)

    drive(-46.67, -46.67, 45) // In front of loader
    turn(-46.67, -58.748) // Could distance reset here, around 180 degrees
    scraper_down()

    drive(-46.67, -58.748, 180) // Ram into loader
    wait(1000, msec) // tune to wait long enough to get the right colored blocks and avoid the wrong color
    scraper_up()

    drive(-46.67, -30.566, 180) // Line up to long goal
    score_long_goal()

    """
}
void Autons::solo()
{
    """
    set_coordinates(14.26, -46.871, 340) // Start against the park zone
    drive(22.111, -22.111, 340) // Eat the blocks in the middle
    turn(14, -14, backwards)
    drive(14, -14, 225) // Drive to the center goal
    score_high_center_goal() // Score only preload just to get AWP
    wait(400, msec)

    drive(46.67, -46.67, 225) // In front of loader
    turn(46.67, -58.748) // Could distance reset here, around 180 degrees
    scraper_down()

    drive(46.67, -58.748, 180) // Ram into loader
    wait(1000, msec) // tune to wait long enough to get the right colored blocks and avoid the wrong color
    scraper_up()

    drive(46.67, -30.566, 180) // Line up to long goal
    score_long_goal()
    wait(4000, msec);

    drive(46.67, -37.813, 180) // Back away from long goal so that the aligner doesn't get stuck when turning
    turn(-22.111, -22.111)
    drive(-22.111, -22.111, 258) // Eat the other blocks in the middle

    drive(-46.67, -46.67, 135) // In front of loader
    turn(-46.67, -58.748) // Could distance reset here, around 180 degrees
    scraper_down()

    drive(-46.67, -58.748, 180) // Ram into loader
    wait(1000, msec) // tune to wait long enough to get the right colored blocks and avoid the wrong color
    scraper_up()

    drive(-46.67, -30.566, 180) // Line up to long goal
    score_long_goal()
    
    """
}