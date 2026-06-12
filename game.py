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
            for i, option in enumerate(options, start=1): print(f"{i}. {option}")
            print(f"{len(options) + 1}. Leave")
            choice = input(">> ").strip()
            if choice.isdigit():
                c_num = int(choice)
                if c_num == len(options) + 1: break
                elif 1 <= c_num <= len(options):
                    print(f"\nYou: \"{options[c_num-1]}\"\n[{self.name}]: {self.dialogue[options[c_num-1]]}")
                    break
            print("Invalid choice.")

# ==============================================================================
# DATA CONFIGURATION & MAIN LOOP
# ==============================================================================
rooms = {"entryway": "You are in the entryway.", "living room": "Living room.", "attic": "Dark attic."}
map_data = {"entryway": {"north": "living room"}, "living room": {"south": "entryway"}}
location = "entryway"
shopkeeper = NPC("Shopkeeper", "Hello!", {"Buy": "Here."})

print("--- TEXT ADVENTURE ---")
while True:
    print(f"\nLocation: {location.title()} - {rooms[location]}")
    action = input("Move/Interact/Q: ").strip().lower()
    if action == "move":
        dirs = list(map_data[location].keys())
        print("Directions:", ", ".join(dirs))
        d = input("Where? ").strip().lower()
        if d in map_data[location]: location = map_data[location][d]
        else: print("Cannot go that way.")
    elif action == "interact": shopkeeper.interact()
    elif action == "q": break
    else: print("Invalid action.")