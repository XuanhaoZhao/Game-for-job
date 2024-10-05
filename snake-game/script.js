const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

let snake = [{ x: 10, y: 10 }];
let food = {};
let direction = { x: 0, y: 0 };
let score = 0;
let gameInterval;

document.getElementById('startButton').addEventListener('click', startGame);
window.addEventListener('keydown', changeDirection);

function startGame() {
    resetGame();
    gameInterval = setInterval(gameLoop, 100);
}

function resetGame() {
    snake = [{ x: 10, y: 10 }];
    direction = { x: 0, y: 0 };
    score = 0;
    document.getElementById('score').innerText = `分数: ${score}`;
    spawnFood();
    if (gameInterval) {
        clearInterval(gameInterval);
    }
}

function spawnFood() {
    food = {
        x: Math.floor(Math.random() * 20),
        y: Math.floor(Math.random() * 20)
    };
}

function changeDirection(event) {
    switch (event.key) {
        case 'ArrowUp':
            direction = { x: 0, y: -1 };
            break;
        case 'ArrowDown':
            direction = { x: 0, y: 1 };
            break;
        case 'ArrowLeft':
            direction = { x: -1, y: 0 };
            break;
        case 'ArrowRight':
            direction = { x: 1, y: 0 };
            break;
    }
}

function gameLoop() {
    updateDirectionFromGamepad(); // 检查手柄输入
    updateSnake();
    draw();
}

function updateDirectionFromGamepad() {
    const gamepads = navigator.getGamepads();
    const gamepad = gamepads[0];

    if (gamepad) {
        // 假设左摇杆控制方向
        const up = gamepad.axes[1] < -0.5; // 向上
        const down = gamepad.axes[1] > 0.5; // 向下
        const left = gamepad.axes[0] < -0.5; // 向左
        const right = gamepad.axes[0] > 0.5; // 向右

        if (up && direction.y === 0) {
            direction = { x: 0, y: -1 };
        }
        if (down && direction.y === 0) {
            direction = { x: 0, y: 1 };
        }
        if (left && direction.x === 0) {
            direction = { x: -1, y: 0 };
        }
        if (right && direction.x === 0) {
            direction = { x: 1, y: 0 };
        }
    }
}

function updateSnake() {
    const head = {
        x: (snake[0].x + direction.x + 20) % 20,
        y: (snake[0].y + direction.y + 20) % 20
    };
    snake.unshift(head);
    if (head.x === food.x && head.y === food.y) {
        score++;
        document.getElementById('score').innerText = `分数: ${score}`;
        spawnFood();
        vibrateGamepad(100); // 吃到食物时震动
    } else {
        if (checkCollision()) {
            vibrateGamepad(200); // 吃到自己时震动
        } else {
            snake.pop();
        }
    }
}

function checkCollision() {
    const head = snake[0];
    // 检查蛇是否碰到自身
    for (let i = 1; i < snake.length; i++) {
        if (head.x === snake[i].x && head.y === snake[i].y) {
            return true;
        }
    }
    return false;
}

function vibrateGamepad(duration) {
    const gamepads = navigator.getGamepads();
    const gamepad = gamepads[0];

    if (gamepad && gamepad.vibrationActuator) {
        gamepad.vibrationActuator.playEffect("dual-rumble", {
            startDelay: 0,
            duration: duration,
            weakMagnitude: 1.0,
            strongMagnitude: 1.0
        });
    }
}

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = 'green';
    snake.forEach(segment => {
        ctx.fillRect(segment.x * 20, segment.y * 20, 18, 18);
    });
    ctx.fillStyle = 'red';
    ctx.fillRect(food.x * 20, food.y * 20, 18, 18);
}
