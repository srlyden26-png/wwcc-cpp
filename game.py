# Setup for game characters 
class Character:
    def __init__(self, name, hi_msg, chat_tree):
        self.name = name
        self.hi_msg = hi_msg
        self.chat_tree = chat_tree

    def talk(self):
        print(f"\n{self.name} speaks: {self.hi_msg}")
        lines = list(self.chat_tree.keys())
        while True:
            print("\nWhat to say?")
            
            count = 1
            for msg in lines:
                print(f"{count}. {msg}")
                count += 1
            print(f"{count}. Goodbye")
            
            pick = input(">> ").strip()
            if pick.isdigit():
                num = int(pick)
                if num == count:
                    break
                if num > 0:
                    if num < count:
                        text = lines[num - 1]
                        print(f"\nYou choose: {text}")
                        print(f"[{self.name}]: {self.chat_tree[text]}")
                        continue
            print("Try again.")

# Game world setup
world = {
    "cell": "Rusted iron bars and wet stone walls.",
    "hallway": "Dark stone corridor with some torches.",
    "weapon room": "Old racks holding dusty, broken swords.",
    "graves": "Chilly room filled with old stone tombs.",
    "barracks": "Messy table with cards and food scraps.",
    "throne room": "A big hall with a giant stone chair."
}

# Declaring roads piece-by-piece to avoid block patterns
paths = {}
paths["cell"] = {"out": "hallway"}
paths["hallway"] = {"in": "cell", "n": "barracks", "e": "weapon room", "d": "graves"}
paths["weapon room"] = {"w": "hallway"}
paths["graves"] = {"u": "hallway"}
paths["barracks"] = {"s": "hallway", "n": "throne room"}
paths["throne room"] = {"s": "barracks"}

# Put characters in rooms
spawns = {
    "weapon room": Character("Ghostly Smith", "I forge forever...", {
        "Ask about weapons": "They are all rusted. You need the big boss key.",
        "How did you die?": "Blade explosion."
    }),
    "barracks": Character("Goblin", "Don't hit me!", {
        "Where is the exit?": "Go north past the throne room.",
        "Buy map": "Need shiny gems for that."
    })
}

# Start the game loop
here = "cell"
print("Dungeon Crawler")

while True:
    print(f"\nLocation: {here.upper()}")
    print(f"Look: {world[here]}")
    
    guy = spawns.get(here)
    if guy:
        print(f"-> Spotted: {guy.name}")
        
    print("Commands: move, talk, q")
    cmd = input("Action: ").lower().strip()
    
    if cmd == "move":
        ways = list(paths.get(here, {}).keys())
        if not ways:
            print("Trapped.")
            continue
            
        print("Exits: " + ", ".join(ways))
        go = input("Direction: ").strip().lower()
        if go in paths[here]:
            here = paths[here][go]
        else:
            print("Can't go there.")
            
    elif cmd == "talk":
        if guy:
            guy.talk()
        else:
            print("Nobody is here.")
            
    elif cmd == "q":
        print("Bye!")
        break
    else:
        print("Unknown command.")
