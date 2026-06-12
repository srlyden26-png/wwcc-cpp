# ==============================================================================
# TEXT-BASED ADVENTURE GAME - DUNGEON EDITION
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
                    break
                elif 1 <= c_num <= len(options):
                    chosen_option = options[c_num-1]
                    print(f"\nYou: \"{chosen_option}\"\n[{self.name}]: {self.dialogue[chosen_option]}")
                    continue 
            print("Invalid choice.")

# ==============================================================================
# DATA CONFIGURATION: DUNGEON MAP & ROOMS
# ==============================================================================
rooms = {
    "prison cell": "A damp, stone cell. The iron bars are rusted through.",
    "dark corridor": "A long hallway lit by flickering torches.",
    "armory": "Racks of broken swords and dusty shields line the walls.",
    "crypt": "Cold stone tombs surround you. A chill fills the air.",
    "guard room": "A messy room with a wooden table, playing cards, and bone remnants.",
    "boss chamber": "A massive room with a towering stone throne."
}

map_data = {
    "prison cell": {"out": "dark corridor"},
    "dark corridor": {"in": "prison cell", "north": "guard room", "east": "armory", "down": "crypt"},
    "armory": {"west": "dark corridor"},
    "crypt": {"up": "dark corridor"},
    "guard room": {"south": "dark corridor", "north": "boss chamber"},
    "boss chamber": {"south": "guard room"}
}

# ==============================================================================
# NPC CONFIGURATION (Linked to specific rooms)
# ==============================================================================
npcs_in_rooms = {
    "armory": NPC("Ghostly Smith", "I forge for eternity...", {
        "Ask about weapons": "Everything here is rusted. You need the Boss's key.",
        "How did you die?": "An accident with a dragon blade."
    }),
    "guard room": NPC("Captured Goblin", "Don't hurt me! I just work here!", {
        "Where is the exit?": "The exit is past the Boss Chamber, to the north!",
        "Buy dynamic map": "I only trade in shiny gems, which you don't have."
    })
}

# ==============================================================================
# MAIN GAME LOOP
# ==============================================================================
location = "prison cell"

print("--- DUNGEON CRAWLER TEXT ADVENTURE ---")
while True:
    print(f"\nLocation: {location.title()}")
    print(f"Description: {rooms[location]}")
    
    # Check if there is an NPC in this room
    current_npc = npns_in_rooms.get(location) if 'npns_in_rooms' in locals() else npcs_in_rooms.get(location)
    if current_npc:
        print(f"You see someone here: {current_npc.name}")
        
    action = input("Move/Interact/Q: ").strip().lower()
    
    if action == "move":
        dirs = list(map_data.get(location, {}).keys())
        if not dirs:
            print("You are completely trapped!")
            continue
            
        print("Directions you can go:", ", ".join(dirs))
        d = input("Where? ").strip().lower()
        if d in map_data[location]:
            location = map_data[location][d]
        else:
            print("Cannot go that way.")
            
    elif action == "interact":
        if current_npc:
            current_npc.interact()
        else:
            print("There is no one here to talk to.")
            
    elif action == "q":
        print("Thanks for playing!")
        break
    else:
        print("Invalid action.")
