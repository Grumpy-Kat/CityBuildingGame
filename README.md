# CityBuildingGame
Simple city building game, inspired by SimCity and written in SDL and C++

---

List of Future Additions:
Fix issues with power and fire maps (does not calculate correctly when deleting power sources and fire sources because does consider other nearby sources)
Give fire station use (stops fire 7/10 in coverage zone)
Fires (ex: affected by fire station coverage and fire budget)
Crime (ex: affected by police station coverage and police budget)
Birth rate and death rate (update population on monthly basis affected by the rates; ex: affected by fire and crime)
Land value (ex: affected by pollution or traffic or crime rates or fire protection, affects population and tax income)
Multiple saves (ex: allow user to choose name)
More buildings (can affect land value; ex: schools, college, stadium, airport, casino, police station)
Educated and uneducated jobs (work with school system; ex: educated == commercial and uneducated == industrial, affects demand based on number of schools)
Pollution (ex: caused by industrial or powerplants, reduces tax payment)
Audio (using SDL_mixer; ex: when placing buildings or getting taxes or taking out loan)
MAYBE Multi-tile buildings (buildings that aren't 1 * 1)
