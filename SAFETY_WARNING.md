# ⚠️ Safety Warning

## Risk Assessment
This software includes a **Stress Test Module** designed to load CPU cores to 100% utilization.

## Potential Risks
1. **Thermal Throttling:** Sustained 100% load may trigger thermal throttling on laptops.
2. **Power Consumption:** Significant increase in power draw during test execution.
3. **System Responsiveness:** System may become sluggish during stress tests.

## Mitigation
- The tool defaults to **Safe Mode** if no flags are provided.
- Stress tests are capped at 5 seconds by default.
- Users should monitor system temperatures (`watch -n 1 sensors`) while running.

## Liability
This software is provided "AS IS". The author is not liable for any hardware damage.
