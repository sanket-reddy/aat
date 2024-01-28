.PHONY: clean All

All:
	@echo "----------Building project:[ bank - Debug ]----------"
	@cd "bank" && "$(MAKE)" -f  "bank.mk"
clean:
	@echo "----------Cleaning project:[ bank - Debug ]----------"
	@cd "bank" && "$(MAKE)" -f  "bank.mk" clean
