const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

let snake = [{ x: 10, y: 10 }];
let food = {};
let direction = { x: 0, y: 0 };
let score = 0;
let gameInterval;

document.getElementById('startButton').addEventListener('click', startGame);
window.addEventListener('keydown', changeDirection);

document.getElementById('stopButton').addEventListener('click', endGame); // 添加结束游戏按钮的监听器

function endGame() {
    clearInterval(gameInterval); // 停止游戏循环
    document.getElementById('score').innerText = `游戏结束，最终分数: ${score}`;
    ctx.clearRect(0, 0, canvas.width, canvas.height); // 清除画布
    // 选填：可以显示一个"游戏结束"的提示
    ctx.font = "40px Arial";
    ctx.fillStyle = "red";
    ctx.textAlign = "center";
    ctx.fillText("游戏结束", canvas.width / 2, canvas.height / 2);
}

function startGame() {
    resetGame();
    gameInterval = setInterval(gameLoop, 100);
}

function resetGame() {
    snake = [{ x: 10, y: 10 }];
    direction = { x: 1, y: 0 }; // 设置初始方向向右
    score = 0;
    document.getElementById('score').innerText = `分数: ${score}`;
    spawnFood();
    if (gameInterval) {
        clearInterval(gameInterval);
    }
}

function spawnFood() {
    let newFood;
    // 重复生成食物，直到它不与蛇的身体重叠
    do {
        newFood = {
            x: Math.floor(Math.random() * 20),
            y: Math.floor(Math.random() * 20)
        };
    } while (isFoodOnSnake(newFood)); // 检查新生成的食物是否与蛇的位置重叠

    food = newFood;
}

function isFoodOnSnake(newFood) {
    // 检查食物是否生成在蛇的身体上
    return snake.some(segment => segment.x === newFood.x && segment.y === newFood.y);
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
        snake.pop();
    }
    
    if (checkCollision()) {
        vibrateGamepad(200); // 吃到自己时震动
        // 结束游戏
        endGame();
    }
}

function checkCollision() {
    const head = snake[0];
    // 检查蛇是否碰到自身，从第二个身体段开始检查
    for (let i = 4; i < snake.length; i++) {
        if (head.x === snake[i].x && head.y === snake[i].y) {
            console.log("Collision detected!"); // 添加这行
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
