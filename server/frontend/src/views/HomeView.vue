<template>
  <main style="height: 100%">
   <n-space>
     <device v-for="device of devices" :key="device.id" :device="device"/>
   </n-space>
  </main>
</template>
<script setup lang="ts">
import Device from "@/components/DeviceComponent.vue";
import {onMounted, ref} from "vue";
import {apiUrl} from "@/main";

const devices = ref<any[]>([])
const getSystemState = async () => {
  const response = await fetch(apiUrl+"/system_state", {
    method: "GET",
    mode: "cors",
  });
  devices.value = await response.json();
}

onMounted(async () => {
  await getSystemState();
  setInterval(() => {
    getSystemState();
  }, 1000)
})

</script>
