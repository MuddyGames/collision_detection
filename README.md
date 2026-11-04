# Practical 7: Collision Detection with cute_c2

In this practical you'll make shapes bump into each other. A player circle follows your mouse and changes colour when it hits an NPC. Your job is to teach it about capsules and rays as well.

By the end you'll understand how games check whether shapes overlap, and how to push them apart when they do.

> Collision detection uses [cute_c2](https://github.com/RandyGaul/cute_headers) by Randy Gaul: a single header file, no setup needed. The project was generated with [raylib project creator](https://raysan5.itch.io/raylib-project-creator) by raysan5.

---

## Short version

If you just want to get going, this is the whole thing in a few lines:

**1. Clone**

```bash
mkdir -p ~/Projects
cd ~/Projects
git clone https://github.com/MuddyGames/collision_detection
```

**2. Set up raylib**

*Linux:*

```bash
cd ~/Projects/collision_detection/setup
bash setup_linux.sh
```

or make the script executable and run it directly:

```bash
cd ~/Projects/collision_detection/setup
chmod +x setup_linux.sh
./setup_linux.sh
```

*Windows* (install [raylib](https://raysan5.itch.io/raylib) first, and then use w64devkit terminal):

```bash
cd ~/Projects/collision_detection/setup
sh setup_windows.sh
```

**3. Build and run**

```bash
cd ~/Projects/collision_detection
make run                            # desktop
```

The rest of this page explains each step, and what to do when the computer says no.

---

## Step 1: Get the project

Keep all your work in a `Projects` folder in your home directory.

- **Linux:** open a terminal.
- **Windows:** open the **w64devkit** terminal (`C:\raylib\w64devkit\w64devkit.exe`).

Then type the same commands on both:

```bash
mkdir -p ~/Projects
cd ~/Projects
git clone https://github.com/MuddyGames/collision_detection
```

Your project now lives in `~/Projects/collision_detection`.

---

## Step 2: Install raylib and Emscripten (once only)

If you set these up for an earlier practical, skip this step. They're shared by every raylib project.

### Linux (Debian, Ubuntu, Pop!_OS or Arch)

```bash
cd ~/Projects/collision_detection/setup
bash setup_linux.sh
```

It will ask for your password to install packages. It takes a few minutes, especially on lab machines.

### Windows

Install the **[raylib installer](https://raysan5.itch.io/raylib)** and keep the default location, `C:\raylib`. Then in the **w64devkit** terminal:

```bash
cd ~/Projects/collision_detection/setup
sh setup_windows.sh
```

When it finishes, close w64devkit and open it again.

> No more MSYS2. Everything now runs in the w64devkit terminal that comes with the raylib installer.

For the manual steps, see the [drawing_primitives README](https://github.com/MuddyGames/drawing_primitives#manual-setup-only-if-the-script-didnt-work-for-you).

---

## Step 3: Build and run

Every command runs from the project folder:

```bash
cd ~/Projects/collision_detection
```

### On your desktop

The same commands work on Linux and Windows (w64devkit):

| Command | What it does |
|---|---|
| `make` | Builds the game |
| `make run` | Builds it and runs it |
| `make BUILD_MODE=DEBUG` | Builds with debug info, for stepping through in the debugger |
| `make clean` | Deletes the `build` folder, so the next build starts fresh |

A window should open with a circle that follows your mouse. Steer it into an NPC and watch it change colour.

### In your browser

```bash
make run_web
```

This builds the web version, starts a small local web server and opens
**<http://127.0.0.1:8000/collision_detection.html>** in your browser.

Press **Ctrl+C** in the terminal to stop the server.

| Command | What it does |
|---|---|
| `make web` | Builds the web version only |
| `make run_web` | Builds it and opens it in your browser |
| `make stop_web` | Stops a web server left running from earlier |

### In VS Code

Open `projects/VSCode/main.code-workspace` (**File → Open Workspace from File…**).

- **Ctrl+Shift+B** builds.
- **F5** builds and starts the debugger. The first time, choose **Debug** in the Run and Debug drop-down.
- **Terminal → Run Task** lists Run, Run Web, Stop Web Server and Clean.

Set a breakpoint inside a collision check, then hover over the shapes to see their positions and sizes. It's the quickest way to find out why two shapes that *look* touching aren't.

---

## How the project is laid out

```
collision_detection/
├── Makefile               build instructions
├── src/
│   ├── main.c             opens the window, runs the game loop
│   ├── game.c             YOUR collision code goes here
│   ├── tests.c            sample collision tests
│   └── cute_c2_impl.c     switches on cute_c2 (leave alone)
├── include/
│   ├── constants.h        screen size and other constants
│   ├── game.h             game functions
│   ├── game_object.h      Player and NPC
│   ├── tests.h            test declarations
│   └── cute_c2.h          the collision library (leave alone)
├── resources/             sprites and images
├── build/                 everything make creates
├── platform/              icons and web page template; leave these alone
└── setup/                 setup scripts (run once)
```

[![](https://mermaid.ink/img/pako:eNqNVduO2jAQ_RXLT60EKCRc88Zmq6pqWaGl-1JAK5MYYimxI9tBUODf13bu2bTCD048Pmfm2DOTXKHPAgxd2O_3t1QSGWHXY1FEBGEUrCXiEvOfRAKPxQkTRGrzK46QfhEhSQTYUsPF_JmgI0fxlgI1vqMYPyOJwO3W799uYBWhC-bABT6jEhEqOmDsCl5WnsJsYYHavLwt35VxvdvCjJHNGpd7NnIDzH9fEmy4IRJAqkXBqGF9e4koObAo-KSkQDGN8gj3o8xbSvWRYxzvMW97NNjF4unpMaSHEpH-x2025zdVKi61NPVmc7ldwk_lHSRf8oR9LQLkYjuwMaEPgNC5AhWH6cChh1D75rFrqclroQ42Z_fle8IIlWJj76oQDVorBmU8RhEwZ2sV3DVb66FcgsxxZcuzkJhHZdb5pIkvNs6uyfeLpvFYSmWd4oeIq0QLgY54Y1tWTrx35LymqUysbx7Vhip3xnU4xjscaX3XBrjqDdMT__ajx56xCBCR0Qg91vWU9xznL9VmVsx-HqxDVkNHTR-maQy8H6_er28to67BNm6xWr8VwHtnFzQu8ASSanmIGJKAd5JNvbeouiGaBlX8nZHzCm_xUXO5f0xJecfXdnWpomq7CHAiQ9MLjVCfW6WxTTsDn-oRM_fntuGSM2EPHjkJoCt5inswxqrH9BIaF1soQxyrj6_uwQAfUBpJ3X6aliD6h7G4YHKWHkPoHlAk1CpNAiRx_hMpIZiqsjE9BV1nZBkf0L3CM3SH9nQwt0bjiTO3nJk1m_TgBbrT4cCeDmeq0SYzZzx3Zvce_GuCWoP5yHKcseWMR7PJZGQPexAHRDK-zP6B5ld4_wCLMhex?type=png)](https://mermaid.live/edit#pako:eNqNVduO2jAQ_RXLT60EKCRc88Zmq6pqWaGl-1JAK5MYYimxI9tBUODf13bu2bTCD048Pmfm2DOTXKHPAgxd2O_3t1QSGWHXY1FEBGEUrCXiEvOfRAKPxQkTRGrzK46QfhEhSQTYUsPF_JmgI0fxlgI1vqMYPyOJwO3W799uYBWhC-bABT6jEhEqOmDsCl5WnsJsYYHavLwt35VxvdvCjJHNGpd7NnIDzH9fEmy4IRJAqkXBqGF9e4koObAo-KSkQDGN8gj3o8xbSvWRYxzvMW97NNjF4unpMaSHEpH-x2025zdVKi61NPVmc7ldwk_lHSRf8oR9LQLkYjuwMaEPgNC5AhWH6cChh1D75rFrqclroQ42Z_fle8IIlWJj76oQDVorBmU8RhEwZ2sV3DVb66FcgsxxZcuzkJhHZdb5pIkvNs6uyfeLpvFYSmWd4oeIq0QLgY54Y1tWTrx35LymqUysbx7Vhip3xnU4xjscaX3XBrjqDdMT__ajx56xCBCR0Qg91vWU9xznL9VmVsx-HqxDVkNHTR-maQy8H6_er28to67BNm6xWr8VwHtnFzQu8ASSanmIGJKAd5JNvbeouiGaBlX8nZHzCm_xUXO5f0xJecfXdnWpomq7CHAiQ9MLjVCfW6WxTTsDn-oRM_fntuGSM2EPHjkJoCt5inswxqrH9BIaF1soQxyrj6_uwQAfUBpJ3X6aliD6h7G4YHKWHkPoHlAk1CpNAiRx_hMpIZiqsjE9BV1nZBkf0L3CM3SH9nQwt0bjiTO3nJk1m_TgBbrT4cCeDmeq0SYzZzx3Zvce_GuCWoP5yHKcseWMR7PJZGQPexAHRDK-zP6B5ld4_wCLMhex)

`main.c` runs the show. Your code goes into four functions in `game.c`:

| Function | When it runs | Put this in it |
|---|---|---|
| `InitGame()` | Once, at the start | Create the player and NPC shapes |
| `UpdateGame()` | Every frame | Move the player, check collisions, push shapes apart |
| `DrawGame()` | Every frame | Draw every shape, coloured by whether it's colliding |
| `CloseGame()` | Once, at the end | Unload any textures |

**Why `cute_c2_impl.c`?** `cute_c2.h` is a single-header library. Every file that includes it gets the declarations, but exactly one `.c` file must also `#define CUTE_C2_IMPLEMENTATION` before including it, to get the actual code. That's all `cute_c2_impl.c` does. Add that define anywhere else and you'll get "multiple definition" errors.

---

## The shapes

cute_c2 has four shapes you'll use:

```c
// Circle: centre and radius
c2Circle circle = { .p = {x, y}, .r = radius };

// AABB (axis-aligned bounding box): a rectangle that never rotates
c2AABB box = { .min = {x, y},              // top-left on screen (smallest x and y)
                .max = {x + w, y + h} };   // bottom-right on screen

// Capsule: a line segment with a radius, like a pill
c2Capsule capsule = { .a = {x1, y1}, .b = {x2, y2}, .r = radius };

// Ray: a starting point, a direction and how far it reaches
c2Ray ray = { .p = {x, y},
              .d = c2Norm(c2V(dx, dy)),   // direction must be length 1
              .t = length };
```

> **raylib's y goes down.** On screen, `min` is the **top-left** corner of an AABB, not the bottom-left as in maths class.

> **Normalise ray directions.** `c2Norm()` makes the direction length 1. Forget it and `t` stops meaning distance.

Converting to raylib for drawing is simple, because a `c2v` and a `Vector2` are both just two floats:

```c
DrawCircleV((Vector2){ circle.p.x, circle.p.y }, circle.r, BLUE);
DrawRectangleLines(box.min.x, box.min.y, box.max.x - box.min.x, box.max.y - box.min.y, GREEN);
```

---

## Hit or not, and how much: manifolds

`c2CircletoCircle(a, b)` just answers **yes or no**. Often you need more: *how far* do they overlap, and *which way* should they move apart? That's a **manifold**:

```c
c2Manifold m;
c2CircletoAABBManifold(player.shape, wall, &m);

if (m.count > 0) {
    // m.n         direction from the player towards the wall (length 1)
    // m.depths[0] how far they overlap
    // m.contact_points[0] where they touch

    // Push the player back out, so it stops at the wall instead of sinking in
    player.shape.p = c2Sub(player.shape.p, c2Mulvs(m.n, m.depths[0]));
}
```

The normal points **from the first shape to the second**, so you subtract it to move the first shape back. The starter code only detects hits; pushing apart is up to you in Task 4.

[![](https://mermaid.ink/img/pako:eNp1VNty2jAQ_RWN-goUSIzB06YD5hLCJQSSh9bmwdgLaGpLHlmelBr-vZJsEzPT8CAknbO7R0drZdhnAWAL1-t1lwoiQrCQzcKQJIRRNAQBvlCzccjeXapZLj1wLz6i16FLkfz1nbc48ARMvAiQ7YUhBFtUrz-ggTMBgRYsTQCtWEJUom0eM9AEu4hEceidgDdiJBiKFL-g2Zo2dDYyj1-qykVBgL6jvRdeuUPNHTlzxmSeI2fp4YiWKzsp8HwcadY4kwB6PcXw41JFxwo929O1PR-d0cTx2zbhfgiC5f_bKq3fHwzO6LFCUjs3FLu_2rypVNNqKi9O0muufJxoWU_Z1fpS12MO5ItpdZGPT7rOT0jOaFbaxLi0Zj0abquUJTuj-Q1jMH8b3YiY6fSLbEx4UvH7245_fXgn4ihdJYmytBS3-Ci-dKbU5xABVZEpFcB1XD8IUMwIFeU1LK5qnp3NbxIjUsbdaFlqLSstmCTaloDQg5QteFp695yT8sVcL17-E1Htknxcae46WzAOukfKE73kQJW7_jjkqLqjjrApGziCJPEOgBLBZc2i1kYne3XWIFJOVW8f1CcSyga9UZOIUwiyBfYkDK0vfhc6fq-KPH6KTD9FZgWy3_tB0K4i8wLZ7QLY76rI8hqz7_n3uIYj4JFHAvk8ZIrnYnGUN-ViS05lsJeGwsUuvUiqlwq2OVEfW-p-alh_ftjS1tdwql0aEk--HNF1N_boL8aiMuTAVakiHGgA3FaNhK1W1-hqNrYy_Adb7Z7R6DZbpmF2W22jhk_Yqt_1eo2W0TYM8868a953epca_quTtxpm12w3my3jvmPKidmpYQiIYHyRP336Bbz8A3xkhyk?type=png)](https://mermaid.live/edit#pako:eNp1VNty2jAQ_RWN-goUSIzB06YD5hLCJQSSh9bmwdgLaGpLHlmelBr-vZJsEzPT8CAknbO7R0drZdhnAWAL1-t1lwoiQrCQzcKQJIRRNAQBvlCzccjeXapZLj1wLz6i16FLkfz1nbc48ARMvAiQ7YUhBFtUrz-ggTMBgRYsTQCtWEJUom0eM9AEu4hEceidgDdiJBiKFL-g2Zo2dDYyj1-qykVBgL6jvRdeuUPNHTlzxmSeI2fp4YiWKzsp8HwcadY4kwB6PcXw41JFxwo929O1PR-d0cTx2zbhfgiC5f_bKq3fHwzO6LFCUjs3FLu_2rypVNNqKi9O0muufJxoWU_Z1fpS12MO5ItpdZGPT7rOT0jOaFbaxLi0Zj0abquUJTuj-Q1jMH8b3YiY6fSLbEx4UvH7245_fXgn4ihdJYmytBS3-Ci-dKbU5xABVZEpFcB1XD8IUMwIFeU1LK5qnp3NbxIjUsbdaFlqLSstmCTaloDQg5QteFp695yT8sVcL17-E1Htknxcae46WzAOukfKE73kQJW7_jjkqLqjjrApGziCJPEOgBLBZc2i1kYne3XWIFJOVW8f1CcSyga9UZOIUwiyBfYkDK0vfhc6fq-KPH6KTD9FZgWy3_tB0K4i8wLZ7QLY76rI8hqz7_n3uIYj4JFHAvk8ZIrnYnGUN-ViS05lsJeGwsUuvUiqlwq2OVEfW-p-alh_ftjS1tdwql0aEk--HNF1N_boL8aiMuTAVakiHGgA3FaNhK1W1-hqNrYy_Adb7Z7R6DZbpmF2W22jhk_Yqt_1eo2W0TYM8868a953epca_quTtxpm12w3my3jvmPKidmpYQiIYHyRP336Bbz8A3xkhyk)

---

## The tasks

Already working in the starter code:

- [x] Circle to Circle
- [x] Circle to AABB
- [x] Circle to Capsule

### Task 1: Explore the starter code

Run it and move the player into each NPC. Then find, in `game.c`:

1. where the player follows the mouse,
2. where each collision is checked,
3. where the colour changes on a hit,
4. how the hit counter and points only go up on the **first** frame of a collision, not every frame the shapes overlap.

### Task 2: Capsule collisions

Add capsule NPCs and check them against the player:

| Check | cute_c2 function |
|---|---|
| Capsule vs AABB | `c2AABBtoCapsule(box, capsule)` |
| Capsule vs Capsule | `c2CapsuletoCapsule(a, b)` |

> Watch the argument order: there is no `c2CapsuletoAABB()`. cute_c2 always puts the "simpler" shape first: circle, then AABB, then capsule.

### Task 3: Ray collisions

Add a ray, for example one from the player towards the mouse, and check it against each NPC:

| Check | cute_c2 function |
|---|---|
| Ray vs Circle | `c2RaytoCircle(ray, circle, &out)` |
| Ray vs AABB | `c2RaytoAABB(ray, box, &out)` |
| Ray vs Capsule | `c2RaytoCapsule(ray, capsule, &out)` |

Rays also tell you **where** they hit:

```c
c2Raycast out;
if (c2RaytoCircle(ray, circle, &out)) {
    c2v hit = c2Impact(ray, out.t);   // the point where the ray hits
    DrawCircleV((Vector2){ hit.x, hit.y }, 4, RED);
}
```

Draw the ray only as far as the hit point, like a laser stopped by the first thing in its way.

[![](https://mermaid.ink/img/pako:eNp9lM-OmzAQxl_Fml4hCv9K8KFSYC89rFQ1eyrk4IJJLBkbGSNtGuXaa6W2p6qHPkafJy_QV6iBbJIViLl47O8334wlzBFyWVDAYNt2JjTTnGKUSM5Zw6RAD1TTXHfZB8JUk4key8ROkXqPnuJMIBNN-3k4yOB9VXNaUaFJX7Uxa9tkMHBdrNPNntR08Nsi236H4vRaRQt0_v1je4f3RJI-SXSF0PnXn39_v91RtyweHJ00YSrnFJ2__kRDuh1B7j20XsfxGPFe-ZC6aaeM_LSrnrK5ZclwETPY4DJFXxj3FTPuesG89CM5GOT7-IIXwr8S042Cm8OoyS1r9MGMEjuoZJzjN_mKvs2jkezOy9687M_KyUvvssyLwh3J7rzszcv-vBxMyFQUYMFOsQKwVi21oKKqIt0Wjh2Sgd6bbzUDbNKClqTlunsFJ1NWE_FJyuqlUsl2twdcEt6YXVsXRNMHRsyDqq6nyjSkKpGt0IAdd9mbAD7CM2A3WC78MAgDL1z5ThiFFhwAe9HCC4OTBV_6VsvFKvQjE6swcrxg6ToW0IJpqR6H59__BSwgrZabg8iH4U7_AUnCN_k?type=png)](https://mermaid.live/edit#pako:eNp9lM-OmzAQxl_Fml4hCv9K8KFSYC89rFQ1eyrk4IJJLBkbGSNtGuXaa6W2p6qHPkafJy_QV6iBbJIViLl47O8334wlzBFyWVDAYNt2JjTTnGKUSM5Zw6RAD1TTXHfZB8JUk4key8ROkXqPnuJMIBNN-3k4yOB9VXNaUaFJX7Uxa9tkMHBdrNPNntR08Nsi236H4vRaRQt0_v1je4f3RJI-SXSF0PnXn39_v91RtyweHJ00YSrnFJ2__kRDuh1B7j20XsfxGPFe-ZC6aaeM_LSrnrK5ZclwETPY4DJFXxj3FTPuesG89CM5GOT7-IIXwr8S042Cm8OoyS1r9MGMEjuoZJzjN_mKvs2jkezOy9687M_KyUvvssyLwh3J7rzszcv-vBxMyFQUYMFOsQKwVi21oKKqIt0Wjh2Sgd6bbzUDbNKClqTlunsFJ1NWE_FJyuqlUsl2twdcEt6YXVsXRNMHRsyDqq6nyjSkKpGt0IAdd9mbAD7CM2A3WC78MAgDL1z5ThiFFhwAe9HCC4OTBV_6VsvFKvQjE6swcrxg6ToW0IJpqR6H59__BSwgrZabg8iH4U7_AUnCN_k)

[![](https://mermaid.ink/img/pako:eNp1lF1vmzAUhv-K5Um9SqoEQhq4mERIP9I2_QjdJg1y4cIhWAMbwWFrVvW_zzGkc7Q1F47t9znnPeYYXmkiU6AeHQ6HsUCOBXhkWVYFlCCQIZeCPDDMY6GBbc2qnDzNY0HUz49CZDWSXxxzoqdQ33DckOHwM5lH61aQE_IEDZLzF94gF1sSKLdNFz3XWBB9ESnUDTKRkoDXSQEKKgreKOueDDS5iN7rIgGrmtYkmx7txoUOOI8SqwdR-v58vjHVC1PtJ0dJzjV2GekD_GPYoxcdZMZd6q0ro9o1231U6ZWGl6oWBak69APYmNr1QTNO0Ck371H_qX6pkdvIT1Ptj5JcshIWDFnPXXdEt7gxF914q7dWxjn2CapCJVtBkjPBkyPHlebvovtK3xrf075hLuW-8xsTuj9Ac4_4PyVPmUhApz_CHg5Y4JGwqjkCWQoEdQnxbwe68U4HPOrjfuVNywpyAZA-s-RHz913RLd4MBfd-Ki31tE37dM3vYFDu9ZaDqOFTFr9ME5I2D6X6rabSRrcqUvik4wXhfcJ7MzKUlMJeiWZwTRxTWXRK1mW2TAylasPldVBscHJHFMJj3zogJZQl4yn6kV_3XMxxVz1NKaemqaQsbbAmMbiTaGsRRnuREI9rFsY0Fq225x6GSsatWqrlCEsOFNdKN93Kya-S1keQrb13qoPh_37HchWIPUsy55omnqv9IV6tu2eutPZ1DpzLfV_5gzojnrDsT0-HTm2O3Mc1zkb2WPrbUB_awMlTCbOeGpPpq47UunsAYWUo6xX3YdMf8_e_gD_w3QP?type=png)](https://mermaid.live/edit#pako:eNp1lF1vmzAUhv-K5Um9SqoEQhq4mERIP9I2_QjdJg1y4cIhWAMbwWFrVvW_zzGkc7Q1F47t9znnPeYYXmkiU6AeHQ6HsUCOBXhkWVYFlCCQIZeCPDDMY6GBbc2qnDzNY0HUz49CZDWSXxxzoqdQ33DckOHwM5lH61aQE_IEDZLzF94gF1sSKLdNFz3XWBB9ESnUDTKRkoDXSQEKKgreKOueDDS5iN7rIgGrmtYkmx7txoUOOI8SqwdR-v58vjHVC1PtJ0dJzjV2GekD_GPYoxcdZMZd6q0ro9o1231U6ZWGl6oWBak69APYmNr1QTNO0Ck371H_qX6pkdvIT1Ptj5JcshIWDFnPXXdEt7gxF914q7dWxjn2CapCJVtBkjPBkyPHlebvovtK3xrf075hLuW-8xsTuj9Ac4_4PyVPmUhApz_CHg5Y4JGwqjkCWQoEdQnxbwe68U4HPOrjfuVNywpyAZA-s-RHz913RLd4MBfd-Ki31tE37dM3vYFDu9ZaDqOFTFr9ME5I2D6X6rabSRrcqUvik4wXhfcJ7MzKUlMJeiWZwTRxTWXRK1mW2TAylasPldVBscHJHFMJj3zogJZQl4yn6kV_3XMxxVz1NKaemqaQsbbAmMbiTaGsRRnuREI9rFsY0Fq225x6GSsatWqrlCEsOFNdKN93Kya-S1keQrb13qoPh_37HchWIPUsy55omnqv9IV6tu2eutPZ1DpzLfV_5gzojnrDsT0-HTm2O3Mc1zkb2WPrbUB_awMlTCbOeGpPpq47UunsAYWUo6xX3YdMf8_e_gD_w3QP)

### Task 4: Push apart

Use manifolds so the player can't pass through **any** NPC, not just the circles. Try `c2CircletoCapsuleManifold()` and `c2CircletoAABBManifold()`.

### Task 5: Test the edges

Collision bugs live at the edges. Check each pair:

1. **Just touching:** shapes exactly side by side.
2. **Fully inside:** one shape completely inside another.
3. **Zero size:** a circle with radius 0, or an AABB with no width (what if the player shrinks?).
4. **Fast movement:** move the player quickly. Does it ever jump straight through a thin wall?

Write down what happens. "It works" is not a test result; "the circle stopped 0 pixels from the wall" is.

---

## Cheat sheet

```c
#include "cute_c2.h"

// Yes or no
c2CircletoCircle(a, b);
c2CircletoAABB(circle, box);
c2CircletoCapsule(circle, capsule);
c2AABBtoAABB(a, b);
c2AABBtoCapsule(box, capsule);
c2CapsuletoCapsule(a, b);

// Rays: true if hit, details in out
c2Raycast out;
c2RaytoCircle(ray, circle, &out);
c2RaytoAABB(ray, box, &out);
c2RaytoCapsule(ray, capsule, &out);
c2v hit = c2Impact(ray, out.t);

// Manifolds: how far, and which way
c2Manifold m;
c2CircletoCircleManifold(a, b, &m);
c2CircletoAABBManifold(circle, box, &m);
c2CircletoCapsuleManifold(circle, capsule, &m);

// Vector maths
c2v v = c2V(x, y);
c2Add(a, b);   c2Sub(a, b);   c2Mulvs(v, s);   c2Norm(v);   c2Len(v);
```

A quick test to drop into `InitGame()`. The results print in the terminal:

```c
c2Circle c1 = { {100, 100}, 50 };
c2Circle c2 = { {180, 100}, 50 };
printf("Circles touching: %s\n", c2CircletoCircle(c1, c2) ? "yes" : "no");   // yes: 80 < 50 + 50
```

---

## When things go wrong

Don't panic. Nine times out of ten it's one of these:

| You see… | What's going on | Fix |
|---|---|---|
| `raylib.h: No such file or directory` | make can't find raylib | Run the setup script again (Step 2) |
| `multiple definition of 'c2…'` | `CUTE_C2_IMPLEMENTATION` is defined in more than one file | Only `cute_c2_impl.c` should define it |
| `undefined reference to 'c2…'` | `cute_c2_impl.c` is missing or was renamed | Make sure it's in `src/` |
| Collision never triggers | Shapes are in different places than you think | Draw every shape, every frame, and check the AABB `min`/`max` order |
| Ray never hits | Direction isn't normalised, or `t` is too short | Use `c2Norm()`, and set `t` to the ray's length |
| Player sinks into shapes | Collision is detected but nothing pushes back | Use a manifold (Task 4) |
| `Emscripten not found in …` (Linux) | Emscripten isn't in `~/emsdk` | Run the setup script (Step 2) |
| `emcc: No such file or directory` (Windows) | Emscripten isn't loaded in this terminal | Close w64devkit and open it again |
| `Address already in use` | A web server from earlier is still running | `make stop_web`, or use another port: `make run_web WEB_PORT=8080` |
| Browser says it can't connect | The page opened before the server was ready | Refresh the page |
| The program still won't build | Old leftover files | `make clean`, then `make` again |

Still stuck? Read the **first** error message, not the last. The first one is usually the real problem; the rest are just complaining about it.

---

## Further reading

- [raylib cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html) and [examples](https://www.raylib.com/examples.html)
- [cute_c2 on GitHub](https://github.com/RandyGaul/cute_headers): read the comments at the top of `cute_c2.h`
- [Collision Detection](https://www.jeffreythompson.org/collision-detection/) by Jeffrey Thompson: the maths behind each check, with diagrams

---

## Before you submit

- [ ] It compiles and runs with no errors or warnings
- [ ] Capsule collisions work against AABBs and other capsules
- [ ] Rays detect circles, AABBs and capsules, and show where they hit
- [ ] The player can't pass through any NPC
- [ ] You've written down what happened in each edge-case test
- [ ] Your code is commented and tidy

Commit early and commit often. A collision with a deadline is the one bug you can't fix afterwards.

Best of luck. Now go make some things bump.