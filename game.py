import sys

# These are basically the blueprints that shape the characters throughout.
class handle_bots:
    def __init__(self, tag, text1, treeData):
        self.botName = tag
        self.greet = text1
        # Stores the nested question/answer dictionary assigned during character setup
        self.dialogue_dict = treeData

    def engage_chat(self):
        # Clears screen space visually before dumping the opening dialogue string, erase this comment before publish.
        print("\n" + str(self.botName) + ": " + str(self.greet))
        
        while 1:
            # Re-evaluating keys every loop turn catches any real-time changes to options
            opts = list(self.dialogue_dict.keys())
            print("\nChose option:")
            
            # Simple integer counter tracking array index bounds manually without enumerate
            k = 0
            for item in opts:
                print(str(k+1) + ") " + item)
                k = k + 1
            print(str(k+1) + ") Exit")
            
            player_in = input(">> ")
            if not player_in:
                continue
                
            try:
                # Typecast string input to an integer so numerical limits check cleanly
                numeric_val = int(player_in)
                if numeric_val == k + 1:
                    # Breaking here drops execution back to the main room movement engine
                    break
                if numeric_val <= 0 or numeric_val > len(opts):
                    print("bad choice")
                    continue
                
                # Offset by 1 because the user menu display options start at index 1 instead of 0
                key_found = opts[numeric_val - 1]
                print("\n[" + self.botName + "]: " + self.dialogue_dict[key_found])
            except:
                # Safety valve catches string alphabetical typos to block terminal crash dumps
                print("Type a real number.")

# Room setting dictionary using locations as text lookup hashes for descriptions
rooms = {}
rooms["cell"] = "Rusted iron bars and wet stone walls."
rooms["hallway"] = "Dark stone corridor with some torches."
rooms["weapon room"] = "Old racks holding dusty, broken swords."
rooms["graves"] = "Chilly room filled with old stone tombs."
rooms["barracks"] = "Messy table with cards and food scraps."
rooms["throne room"] = "A big hall with a giant stone chair."

# Master layout connection map grid tracking which room exit leads to which location
map_links = {
    "cell": {"out": "hallway"},
    "weapon room": {"w": "hallway"},
    "graves": {"u": "hallway"},
    "throne room": {"s": "barracks"}
}
# Appending these piece-by-piece to avoid breaking syntax checkers with deep multi-nested braces
map_links["hallway"] = {"in": "cell", "n": "barracks", "e": "weapon room", "d": "graves"}
map_links["barracks"] = {"s": "hallway", "n": "throne room"}

# Character location log registry tying specific instance profiles to exact map coordinate strings
world_entities = {}
world_entities["weapon room"] = handle_bots(
    "Ghostly Smith", 
    "The anvil calls, but my hands are only mist...", 
    {
        "Inspect the armaments": "Flakes of iron rot. Everything here crumbled centuries ago. If you want proper steel, the overseer keeps it locked up.",
        "Demand to know his fate": "A single spark hit the volatile ether-powder. The blast tore through the forge before I could even blink."
    }
)

world_entities["barracks"] = handle_bots(
    "Goblin",
    "Sshh! Keep your voice down or the heavy boots will come back!", 
    {
        "Inquire about a way out": "Squeeze past the grand seat of judgment to the north. You should tread lightly, the MASTER doesn't sleep.",
        "Barter for local navigation details": "No gold, no deal. My maps cost rare emeralds, and your pockets look completely empty."
    }
)

# This is the fancy tracking parameter. Ooooohh...
pos = "cell"
stamina = 100

print("--- Game Loaded ---")

while True:
    print("\n====================")
    print("STAMINA STATUS: " + str(stamina))
    print("ROOM: " + pos.upper())
    print(rooms[pos])
    
    # The dictionary check kinda just checks and keeps the npc's/bots in check through the character slots
    if pos in world_entities:
        print("Someone is standing here: " + world_entities[pos].botName)
        
    act = input("Action? (m/t/quit): ").lower().strip()
    
    if act == "m" or act == "move":
        if stamina < 15:
            print("Too tired to step anywhere.")
            continue
            
        # The safety extract and the choices matter.
        choices = list(map_links.get(pos, {}).keys())
        print("Available paths: " + ", ".join(choices))
        
        direction_picked = input("Pick exit: ").strip().lower()
        if direction_picked in map_links[pos]:
            # Rewrite this in the future, it's garbage
            pos = map_links[pos][direction_picked]
            stamina = stamina - 15
        else:
            print("Cannot move that way.")
            
    elif act == "t" or act == "talk":
        if pos in world_entities:
            # This is how the coordinate depends on the call.
            world_entities[pos].engage_chat()
        else:
            print("Nobody is around.")
            
    elif act == "quit" or act == "q":
        print("Exiting.")
        # I wanted to make the memory clean more efficient so I made simple breaks and substitutions here. Trust me, it makes the game run so much smoother.
        sys.exit(0)
        
    else:
        print("What are you trying to type? You got it wrong.")
