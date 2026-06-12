# ==============================================================================
# TEXT-BASED ADVENTURE GAME (GitHub Actions/Terminal Compatible)
# ==============================================================================
class NPC:
    def __init__(self, name, greeting, dialogue):
        self.name, self.greeting, self.dialogue = name, greeting, dialogue

    def interact(self):
        print(f"\n[{self.name}]: {self.greeting}")
        options = list(self.dialogue.keys())
        while True:
            print("\nChoose:")
            for i, option in enumerate(options, start=1):
                print(f"{i}. {option}")
            print(f"{len(options) + 1}. Leave")
            
            choice = input(">> ").strip()
            if choice.isdigit():
                c_num = int(choice)
                if c_num == len(options) + 1:
                    break  # Exits the dialogue loop normally
                elif 1 <= c_num <= len(options):
                    chosen_option = options[c_num-1]
                    print(f"\nYou: \"{chosen_option}\"\n[{self.name}]: {self.dialogue[chosen_option]}")
                    # Removed the 'break' here so the player can keep talking until they choose 'Leave'
                    continue 
            print("Invalid choice.")

# ==============================================================================
# DATA CONFIGURATION & MAIN LOOP
# ==============================================================================
rooms = {
    "entryway": "You are in the entryway.", 
    "living room": "Living room.", 
    "attic": "Dark attic."
}

# Fixed: Added connections to the attic so the game doesn't crash
map_data = {
    "entryway": {"north": "living room"},
    "living room": {"south": "entryway", "up": "attic"},
    "attic": {"down": "living room"}
}

location = "entryway"
shopkeeper = NPC("Shopkeeper", "Hello!", {"Buy": "Here.", "Ask about attic": "It's spooky up there."})

print("--- TEXT ADVENTURE ---")
while True:
    print(f"\nLocation: {location.title()} - {rooms[location]}")
    action = input("Move/Interact/Q: ").strip().lower()
    
    if action == "move":
        # Safe check: if room has no exits, show an empty list instead of crashing
        dirs = list(map_data.get(location, {}).keys())
        if not dirs:
            print("There are no exits from this room!")
            continue
            
        print("Directions:", ", ".join(dirs))
        d = input("Where? ").strip().lower()
        if d in map_data[location]:
            location = map_data[location][d]
        else:
            print("Cannot go that way.")
            
    elif action == "interact":
        shopkeeper.interact()
    elif action == "q":
        print("Thanks for playing!")
        break
    else:
        print("Invalid action.")
