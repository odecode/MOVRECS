import asyncio
import aiohttp
import time

API_URL = "http://localhost:8080/calculate/{}"
USER_IDS = range(1, 101)  # Example: user IDs 1 to 10
OUTPUT_FILE = "api_results.txt"

async def fetch(session, user_id):
    url = API_URL.format(user_id)
    async with session.get(url) as response:
        text = await response.text()
        return f"User {user_id}:\n{text}\n"

async def main():
    start_time = time.time()
    async with aiohttp.ClientSession() as session:
        tasks = [fetch(session, user_id) for user_id in USER_IDS]
        results = await asyncio.gather(*tasks)
    elapsed = time.time() - start_time
    with open(OUTPUT_FILE, "w") as f:
        f.write(f"Elapsed time: {elapsed:.2f} seconds\n")
        f.writelines(results)

if __name__ == "__main__":
    asyncio.run(main())
